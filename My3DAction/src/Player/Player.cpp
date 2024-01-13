#include "Player.h"

/**
* @brief Playerのコンストラクタ
*/
Player::Player(Game* Game_)
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
* @note
*/
void Player::initialize(int hit_point)
{
    // 変数初期化
    hitPoint = hit_point;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    rollCoolTime = 0;
    isMove = false;
    rollAble = true;

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
}


/**
* @brief unordered_map初期化メソッド
* @note  各Stateごとのメソッドを登録
*/
void Player::initializeStateFunctions()
{
    stateFunctionMap[PlayerState::Idle] = [this]() { idle();    };  // 待機
    stateFunctionMap[PlayerState::Move] = [this]() { move();    };  // 移動
    stateFunctionMap[PlayerState::Roll] = [this]() { roll();    };  // 前転(回避)
    stateFunctionMap[PlayerState::Attack] = [this]() { attack();  };  // 攻撃
    stateFunctionMap[PlayerState::Damage] = [this]() { damage();  };  // 被ダメージ
    stateFunctionMap[PlayerState::Healing] = [this]() { healing(); };  // 回復
    stateFunctionMap[PlayerState::Death] = [this]() { death();   };  // 死亡
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
        isMove = true;
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


/**
* @brief 移動キーチェック
* @note  条件文を簡潔に
*/
bool Player::checkMoveKey()
{
    return Key_ForwardMove || Key_BackMove || Key_Left_Move || Key_RightMove;
}


/**
* @brief 前転キーチェック
* @note  条件文を簡潔に
*/
bool Player::checkRollKey()
{
    return Key_ForwardRoll || Key_LeftRoll || Key_RightRoll && rollAble;
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
* @brief 状態管理メソッド
* @note  毎フレームの処理
*/
void Player::update()
{
    // 今のStateに対応するメソッド呼び出し
    stateFunctionMap[currentState]();

    // 以下移動中処理 -------------------------------------------------------------------------------------------------
    if (isMove && pGame) {
        // エネミーとの当たり判定
        pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS);
        // 移動後の座標取得
        VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);

        // 当たり判定更新
        // roll以外のとき(Rollのクールタイムがdefault値の時)
        if (rollCoolTime == 0)
            rollAble = pGame->GetCollision()->clampToStageBounds(NewPos, position);
        // roll中の時
        else
        {
            // 当たり判定更新
            pGame->GetCollision()->clampToStageBounds(NewPos, position);
            // Rollのクールダウン
            manageRollCooldown();
        }
    }
    // 以上移動中処理 -------------------------------------------------------------------------------------------------

    // Roll後止まっているときのクールダウン
    if (!rollAble)
        manageRollCooldown();

    // Todo プレイヤーの向きに対する動きがいまいち　以下関数分け
    // レーダーの中心を今の座標と正面の向きに設定
    float Rad = angle * (DX_PI / 180.0f);
    float FrontVecX = -sinf(Rad);
    float FrontVecZ = -cosf(Rad);
    VECTOR FrontVector = VGet(FrontVecX, 0.0f, FrontVecZ);
    pGame->GetRadar()->addCenter(position.x, position.z, FrontVector.x, FrontVector.z);
}


// 以下状態管理メソッド ===============================================================================================
/**
* @brief Idle状態の管理メソッド
*/
void Player::idle()
{
    // 移動ベクトルを初期化
    moveVec = VGet(0.f, 0.f, 0.f);

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
    }
    // healingへ
    else if (Key_Healing) {
        currentState = PlayerState::Healing;
    }
}


/**
* @brief Move状態の管理メソッド
* @note  移動キーを話すとIdle
*/
void Player::move()
{
    if (Key_ForwardMove || PadInput & PAD_INPUT_UP)
    {
        // アニメーション、移動動作をセット
        animateAndMove(ePlayer::AnimationNum::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // アニメーションタイマーリセット
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Down => Runモーション(3) 下移動
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        animateAndMove(ePlayer::AnimationNum::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Right => Runモーション(3) 右移動
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Left => Runモーション(3) 左移動
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    else
    {
        currentState = PlayerState::Idle;
        isMove = false;
    }
}


/**
* @brief Roll状態の管理メソッド
* @note  アニメーション終了時にIdle
*/
void Player::roll()
{
    // Space or PAD_× => Roll
    if (Key_ForwardRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        isRoll = true;
    }
    // 右Roll
    if (Key_RightRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }
    // 左Roll
    if (Key_LeftRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
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
            isMove = false;
        }
    }
}


/**
* @brief Attack状態の管理メソッド
*/
void Player::attack()
{
    if (Key_Attack)
    {
        // アニメーションをセット
        if (!isAttackAnim)       // (int)ePlayerWS::Slash1と(int)ePlayer::Idleが同じなので条件を変更
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash1;
            setAnim(animHandle, animNum, animTimer);
            isAttackAnim = true;
        }
    }

    if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash1)], &animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        // モデルを戻す
        if (pGame)
            animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
        currentState = PlayerState::Idle;
        isAttackAnim = false;
    }

}


/**
* @brief Damage状態の管理メソッド
* @norte HPの減少
*/
void Player::damage()
{
}


/**
* @brief Healing状態の管理メソッド
* @note  HPの回復　アニメーション終了時にIdle
*/
void Player::healing()
{
    // F => Drinking 回復時モーション
    if (Key_Healing)
    {
        // アニメーションをセット
        if (animNum != (int)ePlayer::AnimationNum::Drinking)  // ここがないとanimTimerがうまくリセットされない
        {
            animNum = (int)ePlayer::AnimationNum::Drinking;
            setAnim(animHandle, animNum, animTimer);
        }

    }

    // アニメーション終了後
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Drinking)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        // ここでHP回復
        currentState = PlayerState::Idle;
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

    // アニメーション終了後、死亡フラグをtrueに
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Dying)], &animTimer, PLAYER_ANIM_F_INCREMENT))
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
    if (hitPoint <= 0.f)
    {
        if (isDeath)
        {
            return false;
        }
        // 先に入る
        else
        {
            // 死亡状態へ
            currentState = PlayerState::Death;
        }
    }

#ifdef _DEBUG
    // LでHP減少
    if (CheckHitKey(KEY_INPUT_L)) {
        hitPoint = clamp(hitPoint, 0, MAX_HP); // 最大最小を決定
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

    //VECTOR rotate = MV1GetRotationXYZ(anim_handle);
    //int nRotateY = static_cast<int>(rotate.y);
    //DrawFormatString(0, 0, GetColor(0, 0, 0), "nRotateY:%d",nRotateY);

    // 3Dモデルの描画
    MV1DrawModel(animHandle);

    // 
    MV1SetAttachAnimTime(animHandle, static_cast<int>(ePlayer::AnimationNum::Slash1), animTimer);
    // 41が右手のBone
    MATRIX FrameMatrix = MV1GetFrameLocalWorldMatrix(animHandle, 41);
#ifdef _DEBUG    
    VECTOR pos = VGet(0.f, 0.f, 0.f);
    pos = VTransform(pos, FrameMatrix);
    DrawSphere3D(pos, 10.f, 10, BLUE, BLUE, TRUE);

    // 当たり判定カプセル描画
    DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);
#endif

}


/**
* @brief Hpを取得して返す
*/
float Player::GetHp()
{
    return hitPoint;
}

