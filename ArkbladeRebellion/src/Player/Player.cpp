#include "Player.h"


// コンストラクタ
Player::Player(Game *Game)
{
    pGame = Game;

    // モデル取得
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
}


/*
    デストラクタ
    ポインタpGameのDeleteはGameクラスでしているので、記述の必要なし
*/
Player::~Player()
{
    SAFE_DELETE_ARRAY(animTimes);
    SAFE_DELETE_ARRAY(withSwordAnimTimes);
}


// 初期化メソッド
void Player::initialize(int hit_point)
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
    MV1AttachAnim(animHandle, static_cast<int>(ePlayer::AnimationNum::Idle));

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


// unordered_map初期化メソッド
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


// 移動時の行動管理
void Player::animateAndMove(ePlayer::AnimationNum num, float rotate_angle, float move_x, float move_z)
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
        angle = rotate_angle - pGame->GetCamera()->GetHorizontalAngle();
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


// 移動キーチェック
bool Player::checkMoveKey()
{
    return Key_ForwardMove || Key_BackMove || Key_Left_Move || Key_RightMove;
}


// 回転キーチェック
bool Player::checkRollKey()
{
    return Key_ForwardRoll || Key_LeftRoll || Key_RightRoll || Key_BackRoll && rollAble;
}


// 移動後の座標を設定する
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
            pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, ENEMY_CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS, CHARA_HIT_PUSH_POWER);
            // 移動後の座標取得
            VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
            // 地面との判定があるときはRoll可能
            rollAble = pGame->GetCollision()->clampToStageBounds(NewPos, position);
        }
        // roll中の時
        else
        {
            // エネミーとの当たり判定
            pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, ENEMY_CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS, 0.f);
            // 移動後の座標取得
            VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
            // 当たり判定更新
            pGame->GetCollision()->clampToStageBounds(NewPos, position);
            // Rollのクールダウン
            manageRollCooldown();
        }
    }

}


// Rollのクールダウン管理メソッド
void Player::manageRollCooldown()
{
    // クールタイムを減らす
    rollCoolTime -= PLAYER_ANIM_F_INCREMENT;

    // クールタイムが0以下
    if (rollCoolTime <= 0)
    {
        // クールタイムをdefaultに
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::Roll)];

        rollAble = true;
    }
}


// AttackからIdleに戻る際の処理メソッド
void Player::changeAttackToIdle()
{
    // モデルを戻す
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
    // StateをIdleへ
    currentState = PlayerState::Idle;
    isAttackAnim = false;
}


// 状態管理メソッド
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
        hitPoint = clamp(hitPoint -= ENEMY_ATTACK, 0, MAX_HP); // 最大最小を決定
    }

    // hitPoint0以下でdeathへ
    if (hitPoint <= 0 && !isDeath)
        currentState = PlayerState::Death;
}


// 以下状態管理メソッド ===============================================================================================
// Idle状態の管理
void Player::idle()
{
    // 移動ベクトルを初期化
    moveVec = VGet(0.f, 0.f, 0.f);
    // 攻撃ヒットフラグを折る
    isAttackHit = false;

    // アニメーションをセット
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Idle))  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Idle);
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
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::Roll)];

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


// Move状態の管理
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


// Roll状態の管理
void Player::roll()
{
    // 移動後の座標を設定
    moveHandle();

    // 前Roll
    if (Key_ForwardRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, FORWARD_ROTATION_ANGLE, 0, PLAYER_ROLL_SPEED);
        isRoll = true;
    }
    // 右Roll
    else if (Key_RightRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, RIGHT_ROTATION_ANGLE, PLAYER_ROLL_SPEED, 0);
        isRoll = true;
    }
    // 左Roll
    else if (Key_LeftRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, LEFT_ROTATION_ANGLE, -PLAYER_ROLL_SPEED, 0);
        isRoll = true;
    }
    // 後Roll
    else if (Key_BackRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, BACK_ROTATION_ANGLE, 0, -PLAYER_ROLL_SPEED);
        isRoll = true;
    }

    // アニメーション終了後
    if (rollAble)
    {
        if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Roll)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            currentState = PlayerState::Idle;
            rollAble = false;
            isRoll = false;
        }
    }
}


// Attack状態の管理
void Player::attack()
{
    // 一段目の攻撃 ===================================================================================================================
    if (isFirst)
    {
        //count += PLAYER_ANIM_F_INCREMENT;

        // アニメーションをセット
        if (!isAttackAnim)  // static_cast<int>(ePlayerWS::Slash1)とstatic_cast<int>(ePlayer::Idle)が同じなので条件を変更
        {
            animNum = static_cast<int>(ePlayerWS::AnimationNum::Slash1);
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
    else if (isSecond)
    {
        //count += PLAYER_ANIM_F_INCREMENT

        if (animNum != static_cast<int>(ePlayerWS::AnimationNum::Slash2))
        {
            animNum = static_cast<int>(ePlayerWS::AnimationNum::Slash2);
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
    else if (isThird)
    {
        if (animNum != static_cast<int>(ePlayerWS::AnimationNum::Slash3))
        {
            animNum = static_cast<int>(ePlayerWS::AnimationNum::Slash3);
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

    // 剣OBB描画
    if (CheckHitKey(KEY_INPUT_E))
        mOBBColSword.draw(WHITE);

    // 武器OBB,敵OBBでの当たり判定
    if (pGame->GetCollision()->checkOBBCol(mOBBColSword, pGame->GetEnemy()->GetOBBCol()))
    {
        isAttackHit = true;
    }
}


// Damage状態の管理
void Player::damage()
{
    // 現在のHP更新
    currentHP = hitPoint;
    // アニメーションをセット
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Damage))  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Damage);
        setAnim(animHandle, animNum, animTimer);
    }

    // アニメーション終了後
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Damage)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        currentState = PlayerState::Idle;

}


// Healing状態の管理
void Player::healing()
{
    // アニメーションをセット
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Drinking))  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Drinking);
        setAnim(animHandle, animNum, animTimer);
    }

    // アニメーション終了後
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Drinking)], &animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        // HP回復 最大最小を決定
        hitPoint = clamp(hitPoint += HEALING_VALUE, 0, MAX_HP);
        // 回復可能回数を減らす
        healCount--;
        // Idleへ
        currentState = PlayerState::Idle;
    }
}


/*
    Death状態の管理
    HPが0でここに入る
    アニメーション終了時、ゲーム終了
*/
void Player::death()
{
    // アニメーションをセット
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Dying))  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Dying);
        setAnim(animHandle, animNum, animTimer);
    }

    // アニメーション再生 =======================
    animTimer += PLAYER_ANIM_F_INCREMENT;
    // 死亡時はanimTimerをリセットしないのでここで処理     アニメーション終了時にflagON
    if (animTimer >= animTimes[static_cast<int>(ePlayer::AnimationNum::Dying)])
        isDeath = true;
}
// 以上状態管理メソッド ===============================================================================================


// 生き死にを結果として返す
bool Player::isAlive()
{
    // hitPointが0以下
    if (hitPoint <= 0 && isDeath)
        return false;

    return true;
}


// 描画メソッド
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

    // 当たり判定カプセル描画
    if (CheckHitKey(KEY_INPUT_Q))
        DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);

    // OBB描画
    if (CheckHitKey(KEY_INPUT_E))
    {
        // 当たっているときは赤色に
        if (pGame->GetEnemy()->GetIsHitFlag())
            mOBBCol.draw(RED);
        else
            mOBBCol.draw(WHITE);
    }

}


// healCountを取得して返す
int Player::GetHealCount()
{
    return healCount;
}


// mOBBColを取得して返す 
OBBCollider Player::GetOBBCol()
{
    return mOBBCol;
}