#include "Player.h"

/**
* @brief Playerのコンストラクタ
*/
Player::Player(Game *Game_)
{
    pGame = Game_;

    // モデル取得
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
}


/**
* @brief デストラクタ
* @note  ポインタpGameのDeleteはGameクラスでしているので、記述の必要なし
*/
Player::~Player()
{
    delete[] animTimes;
    delete[] withSwordAnimTimes;
}


/**
* @brief 初期化メソッド
* @param[in] hit_point　キャラのHP　拡張性向上のため
*/
void Player::initialize(float hit_point)
{
    // 変数初期化
    hitPoint = hit_point;
    currentHP = hitPoint;
    healCount = MAX_HEAL_COUNT;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    rollCoolTime = 0.f;
    rollAble = true;
    isAttackHit = false;

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, (int)ePlayer::AnimationNum::Idle);

    // unordered_map初期化
    initializeStateFunctions();

    // animTimesのサイズを指定　アニメーション番号最後尾 + 1
    animTimes = new float[static_cast<int>(ePlayer::AnimationNum::Dying) + 1];
    // アニメーション時間を取得
    for (int i = static_cast<int>(ePlayer::AnimationNum::Idle); i <= static_cast<int>(ePlayer::AnimationNum::Dying); i++)
    {
        animTimes[i] = MV1GetAnimTotalTime(animHandle, i);
    }

    // 武器を所持したモデルのアニメーション時間を取得
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::PlayerWithSword);
    withSwordAnimTimes = new float[static_cast<int>(ePlayerWS::AnimationNum::Slash3) + 1];
    for (int i = static_cast<int>(ePlayerWS::AnimationNum::Idle); i <= static_cast<int>(ePlayerWS::AnimationNum::Slash3); i++)
    {
        withSwordAnimTimes[i] = MV1GetAnimTotalTime(animHandle, i);
    }

    // モデルを戻す
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);

    // 体用 OBBColliderインスタンス化   被ダメージ時使用
    mOBBCol = OBBCollider(PLAYER_OBB_SCALE, PLAYER_OBB_ANGLE, PLAYER_OBB_TRANS);

    // 剣用 OBBColliderインスタンス化   攻撃時使用
    mOBBColSword = OBBCollider(SWORD_OBB_SCALE, SWORD_OBB_ANGLE, SWORD_OBB_TRANS);
}


/**
* @brief unordered_map初期化メソッド
* @note  各Stateごとのメソッドを登録
*/
void Player::initializeStateFunctions()
{
    stateFunctionMap[PlayerState::Idle]     = [this]() { idle();    };  // 待機
    stateFunctionMap[PlayerState::Move]     = [this]() { move();    };  // 移動
    stateFunctionMap[PlayerState::Roll]     = [this]() { roll();    };  // 前転(回避)
    stateFunctionMap[PlayerState::Attack]   = [this]() { attack();  };  // 攻撃
    stateFunctionMap[PlayerState::Damage]   = [this]() { damage();  };  // 被ダメージ
    stateFunctionMap[PlayerState::Healing]  = [this]() { healing(); };  // 回復
    stateFunctionMap[PlayerState::Death]    = [this]() { death();   };  // 死亡
}


/**
* @brief 移動時の行動管理
* @note  アニメーションと向きの設定をする
*        moveFlagはここでtrueに
* @param[in] num　	        アニメーション番号
* @param[in] ROTATE_ANGLE　	回転角度
* @param[in] move_x　	    x軸方向の移動スピード
* @param[in] move_z　	    z軸方向の移動スピード
*/
void Player::animateAndMove(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z)
{
    // アニメーションをセット
    if (animNum != static_cast<int>(num))  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(num);
        setAnim(animHandle, animNum, animTimer);
    }

    // 移動する向きと速度を設定
    if (animNum == static_cast<int>(num))
    {
        angle = ROTATE_ANGLE - pGame->GetCamera()->GetHorizontalAngle();
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


/**
* @brief 　移動キーチェック
* @details 条件文を簡潔に
*/
bool Player::checkMoveKey()
{
    return Key_ForwardMove || Key_BackMove || Key_Left_Move || Key_RightMove;
}


/**
* @brief 　回転キーチェック
* @details 条件文を簡潔に
*/
bool Player::checkRollKey()
{
    return Key_ForwardRoll || Key_LeftRoll || Key_RightRoll || Key_BackRoll && rollAble;
}


/**
* @brief 移動後の座標を設定する
* @note  移動時に呼び出し
*/
void Player::moveHandle()
{
    // モデルの座標・向きをもとに値設定
    VECTOR ObbAngle = VGet(0.f, angle, 0.f);
    VECTOR ObbTrans = VGet(position.x, position.y + PLAYER_OBB_TRANS_Y, position.z);

    // OBB値変更
    mOBBCol.changeRotateMatrix(ObbAngle);      // 回転
    mOBBCol.changeTranslateMatrix(ObbTrans);   // 移動

    if (pGame)
    {
        // 当たり判定更新 ------
        // roll以外のとき(ゲーム開始時)
        if (!isRoll)
        {            
            // エネミーとの当たり判定
            pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS, CHARA_HIT_PUSH_POWER);
            // 移動後の座標取得
            VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
            // 地面との判定があるときはRoll可能
            rollAble = pGame->GetCollision()->clampToStageBounds(NewPos, position);
        }
        // roll中の時
        else
        {
            // エネミーとの当たり判定
            pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS, 0.f);
            // 移動後の座標取得
            VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
            // 当たり判定更新
            pGame->GetCollision()->clampToStageBounds(NewPos, position);
            // Rollのクールダウン
            manageRollCooldown();
        }
    }

}


/**
* @brief Rollのクールダウン管理メソッド
* @note  クールタイムを減らし、0になるとRollをできるように
*/
void Player::manageRollCooldown()
{
    // クールタイムを減らす
    rollCoolTime -= PLAYER_ANIM_F_INCREMENT;

    // クールタイムが0以下
    if (rollCoolTime <= 0)
    {
        // クールタイムをdefaultに
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::NoMoveRoll)];

        rollAble = true;
    }
}


/**
* @brief AttackからIdleに戻る際の処理メソッド
*/
void Player::changeAttackToIdle()
{
    // モデルを戻す
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
    // StateをIdleへ
    currentState = PlayerState::Idle;
    isAttackAnim = false;
}


/**
* @brief 状態管理メソッド
* @note  毎フレームの処理
*/
void Player::update()
{
    // 今のStateに対応するメソッド呼び出し
    stateFunctionMap[currentState]();

    // Roll後止まっているときのクールダウン
    if (!rollAble)
        manageRollCooldown();

    // 攻撃を受けた時      Roll中は無敵
    if (pGame->GetEnemy()->GetIsHitFlag() && !isRoll)
    {
        hitPoint = clampF(hitPoint, 0, MAX_HP); // 最大最小を決定
        hitPoint -= ENEMY_ATTACK;
    }

    // hitPoint0以下でdeathへ
    if (hitPoint <= 0.f && !isDeath)
        currentState = PlayerState::Death;
}


// 以下状態管理メソッド ===============================================================================================
/**
* @brief Idle状態の管理メソッド
*/
void Player::idle()
{
    // 移動ベクトルを初期化
    moveVec = VGet(0.f, 0.f, 0.f);
    // 攻撃ヒットフラグを折る
    isAttackHit = false;

    // アニメーションをセット
    if (animNum != (int)ePlayer::AnimationNum::Idle)  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = (int)ePlayer::AnimationNum::Idle;
        setAnim(animHandle, animNum, animTimer);
    }
    updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Idle)], &animTimer, PLAYER_ANIM_F_INCREMENT);

    // 遷移 ------------------------------------------------------------------------------------------
    if (checkMoveKey()) {
        currentState = PlayerState::Move;
    }
    else if (checkRollKey() && rollAble) {
        currentState = PlayerState::Roll;
        /*
            ローリングのクールタイムを追加
            roll_coolTime = Const.MAX_ROLLING_COOLTIME + animTime;
        */
        // animTimeをRollの数にするように、配列を作成して取得
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::NoMoveRoll)];

    }
    // attackへ
    else if (Key_Attack) {
        currentState = PlayerState::Attack;
        // 武器を持ったモデルに変更
        if (pGame)
            animHandle = pGame->GetModelManager()->GetHandle(ModelType::PlayerWithSword);
        isFirst = true;
    }
    // healingへ
    else if (Key_Healing && healCount > 0) {
        currentState = PlayerState::Healing;
    }
    // HP減少時　Damageへ    HPが0以下の際には通らずDeathへ
    if (hitPoint < currentHP && hitPoint > 0) {
        currentState = PlayerState::Damage;
    }
}


/**
* @brief Move状態の管理メソッド
* @note  移動キーを話すとIdle
*/
void Player::move()
{
    // 移動後の座標を設定
    moveHandle();

    if (Key_ForwardMove)
    {
        // アニメーション、移動動作をセット
        animateAndMove(ePlayer::AnimationNum::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // アニメーションタイマーリセット
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Down => Runモーション(3) 下移動
    else if (Key_BackMove)
    {
        animateAndMove(ePlayer::AnimationNum::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Right => Runモーション(3) 右移動
    else if (Key_RightMove)
    {
        animateAndMove(ePlayer::AnimationNum::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Left => Runモーション(3) 左移動
    else if (Key_Left_Move)
    {
        animateAndMove(ePlayer::AnimationNum::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    else
    {
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Roll状態の管理メソッド
* @note  アニメーション終了時にIdle
*/
void Player::roll()
{
    // 移動後の座標を設定
    moveHandle();

    // 前Roll
    if (Key_ForwardRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        isRoll = true;
    }
    // 右Roll
    else if (Key_RightRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }
    // 左Roll
    else if (Key_LeftRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }
    // 後Roll
    else if (Key_BackRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, BACK_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        isRoll = true;
    }

    // アニメーション終了後
    if (rollAble)
    {
        if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::NoMoveRoll)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            currentState = PlayerState::Idle;
            rollAble = false;
            isRoll = false;
        }
    }
}


/**
* @brief Attack状態の管理メソッド
*/
void Player::attack()
{
    // 一段目の攻撃 ===================================================================================================================
    if (isFirst)
    {
        //count += PLAYER_ANIM_F_INCREMENT;

        // アニメーションをセット
        if (!isAttackAnim)       // (int)ePlayerWS::Slash1と(int)ePlayer::Idleが同じなので条件を変更
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash1;
            setAnim(animHandle, animNum, animTimer);
            isAttackAnim = true;
        }
        // アニメーション終了後
        if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash1)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            isFirst = false;
            isAttackAnim = false;
        }
        // 二段目へ行くかどうか
        if (!isAttackAnim)
        {
            // Bキーを押している            countが43秒以上　アニメーション45秒の2秒前までに押す
            if (CheckHitKey(KEY_INPUT_B)/*  && count >= 43 */)
            {
                // 二段目へ
                isSecond = true;
                isAttackAnim = true;
            }
            // Idleへ戻る
            else/* if (count >= 50 ) // 五秒猶予 */
            {
                changeAttackToIdle();
            }
        }

    }

    // 二段目の攻撃 ===================================================================================================================
    if (isSecond)
    {
        //count += PLAYER_ANIM_F_INCREMENT

        if (animNum != (int)ePlayerWS::AnimationNum::Slash2)
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash2;
            setAnim(animHandle, animNum, animTimer);
            //count = 0;
        }
        // アニメーション終了後
        if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash2)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            isSecond = false;
            // アニメーション終了フラグをfalseに　二段目に行くかどうかを判定する用
            isAttackAnim = false;
        }
        // 三段目に行くかどうか
        if (!isAttackAnim)
        {
            // Nキーを押している        countが48秒以上　アニメーション50秒の2秒前までに押す
            if (CheckHitKey(KEY_INPUT_N)/*  && count >= 48 */)
            {
                // 三段目へ
                isThird = true;
                isAttackAnim = true;
            }
            // Idleへ戻る
            else
            {
                changeAttackToIdle();
            }
        }
    }

    // 三段目の攻撃 ===================================================================================================================
    if (isThird)
    {
        if (animNum != (int)ePlayerWS::AnimationNum::Slash3)
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash3;
            setAnim(animHandle, animNum, animTimer);
            //count = 0;
        }
        // アニメーション終了後
        if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash3)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            // Idleへ戻る
            changeAttackToIdle();
            isThird = false;
        }
    }

    // 当たり判定(剣)設定 ==============================================
    // アニメーションがアタッチされている必要があるのでここで処理
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
    // モデルの右手frame取得
    MATRIX frame_matrix = MV1GetFrameLocalWorldMatrix(animHandle, PLAYER_RIGHT_HAND_FRAME);
    // 親の行列に合わせる
    mOBBColSword.setParentMatrix(frame_matrix);
#ifdef _DEBUG
    // 描画
    mOBBColSword.draw();
#endif

    // 武器OBB,敵OBBでの当たり判定
    if (pGame->GetCollision()->checkOBBCol(mOBBColSword, pGame->GetEnemy()->GetOBBCol()))
    {
        isAttackHit = true;
    }
}


/**
* @brief Damage状態の管理メソッド
* @norte HPの減少
*/
void Player::damage()
{
    // 現在のHP更新
    currentHP = hitPoint;
    // アニメーションをセット
    if (animNum != (int)ePlayer::AnimationNum::Damage)  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = (int)ePlayer::AnimationNum::Damage;
        setAnim(animHandle, animNum, animTimer);
    }

    // アニメーション終了後
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Damage)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        currentState = PlayerState::Idle;

}


/**
* @brief Healing状態の管理メソッド
* @note  HPの回復　アニメーション終了時にIdle
*/
void Player::healing()
{
    // アニメーションをセット
    if (animNum != (int)ePlayer::AnimationNum::Drinking)  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = (int)ePlayer::AnimationNum::Drinking;
        setAnim(animHandle, animNum, animTimer);
    }

    // アニメーション終了後
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Drinking)], &animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        // ここでHP回復
        hitPoint += HEALING_VALUE;
        // 最大最小を決定
        hitPoint = clampF(hitPoint, 0, MAX_HP);
        // 回復可能回数を減らす
        healCount--;
        // Idleへ
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Death状態の管理メソッド
* @note  HPが0でここ　アニメーション終了時、ゲーム終了
*/
void Player::death()
{
    // アニメーションをセット
    if (animNum != (int)ePlayer::AnimationNum::Dying)  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = (int)ePlayer::AnimationNum::Dying;
        setAnim(animHandle, animNum, animTimer);
    }

    // アニメーション再生 =======================
    animTimer += PLAYER_ANIM_F_INCREMENT;
    // 死亡時はanimTimerをリセットしないのでここで処理     アニメーション終了時にflagON
    if (animTimer >= animTimes[static_cast<int>(ePlayer::AnimationNum::Dying)])
        isDeath = true;
}
// 以上状態管理メソッド ===============================================================================================


/**
* @brief  生き死にを結果として返す
* @return true:生存 / false:死亡
*/
bool Player::isAlive()
{
    // hitPointが0以下
    if (hitPoint <= 0.f && isDeath)
        return false;

#ifdef _DEBUG
    // LでHP減少
    if (CheckHitKey(KEY_INPUT_H)) {
        hitPoint = clampF(hitPoint, 0, MAX_HP); // 最大最小を決定
        hitPoint -= HP_CHANGE_AMOUNT;
    }
#endif

    return true;
}


/**
* @brief 描画メソッド
* @note  プレイヤーを追従するためカメラ用関数はここで呼び出す
*/
void Player::draw()
{
    // モデルにタイマーセット
    // これがないとアニメーションしない
    MV1SetAttachAnimTime(animHandle, 0, animTimer);

    // モデルの大きさ変更
    MV1SetScale(animHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // モデルの回転
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // 3Dモデルに座標をセット
    MV1SetPosition(animHandle, position);

    // 3Dモデルの描画
    MV1DrawModel(animHandle);

    // 
    MV1SetAttachAnimTime(animHandle, static_cast<int>(ePlayerWS::AnimationNum::Slash1), animTimer);
    // 55が右手のBone
    MATRIX FrameMatrix = MV1GetFrameLocalWorldMatrix(animHandle, 55);
#ifdef _DEBUG    
    VECTOR pos = VGet(0.f, 0.f, 0.f);
    pos = VTransform(pos, FrameMatrix);
    DrawSphere3D(pos, 10.f, 10, BLUE, BLUE, TRUE);

    // 当たり判定カプセル描画
    //DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);

    // 描画
    mOBBCol.draw();
#endif

}


/**
* @brief healCountを取得して返す
*/
int Player::GetHealCount()
{
    return healCount;
}


/*
* @brief mOBBColを取得して返す
*/
OBBCollider Player::GetOBBCol()
{
    return mOBBCol;
}