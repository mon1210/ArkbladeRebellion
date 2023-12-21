#include "Player.h"

/**
* @brief Playerのコンストラクタ
*/
Player::Player(Game *Game_)
{
    hitPoint = MAX_HP;

    pGame = Game_;
    
    // モデル取得
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);

    angle = PLAYER_START_ROTATE_Y;

    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, (int)ePlayer::AnimationNum::Idle);

    // unordered_map初期化
    initializeStateFunctions();
}


/**
* @brief デストラクタ
* @note  ポインタのDeleteはGameクラスでしているので、記述の必要なし
*/
Player::~Player()
{
}


// Roll時、長押しで回転し続けられるのを直すようにもしたい
// Todo
// void RollHandle(){}


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
        setAnim(animHandle, animNum, animTime, animTimer);
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
* @brief unordered_map初期化メソッド
* @note  各Stateごとのメソッドを登録
*/
void Player::initializeStateFunctions()
{
    stateFunctionMap[PlayerState::Idle]     = [this]() { Idle();    };  // 待機
    stateFunctionMap[PlayerState::Move]     = [this]() { Move();    };  // 移動
    stateFunctionMap[PlayerState::Roll]     = [this]() { Roll();    };  // 前転(回避)
    stateFunctionMap[PlayerState::Attack]   = [this]() { Attack();  };  // 攻撃
    stateFunctionMap[PlayerState::Damage]   = [this]() { Damage();  };  // 被ダメージ
    stateFunctionMap[PlayerState::Healing]  = [this]() { Healing(); };  // 回復
    stateFunctionMap[PlayerState::Death]    = [this]() { Death();   };  // 死亡
}


/**
* @brief 状態管理メソッド
* @note  毎フレームの処理
*/
void Player::update()
{
    // 今のStateに対応するメソッド呼び出し
    stateFunctionMap[currentState]();

    // 移動した場合の当たり判定更新と座標セット
    if (isMove && pGame) {
        // エネミー座標取得
        VECTOR EnemyPos = pGame->GetEnemy()->GetPos();
        // エネミーとの当たり判定
        pGame->GetCollision()->charaCapCol(position, moveVec, EnemyPos, CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS);
        // 移動後の座標取得
        VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
        // 当たり判定更新
        pGame->GetCollision()->clampToStageBounds(NewPos, position, rollAble);
    }

    // Todo プレイヤーの向きに対する動きがいまいち　以下関数分け
    // レーダーの中心を今の座標と正面の向きに設定
    float Rad = angle * (DX_PI / 180.0f);
    float FrontVecX = -sinf(Rad);
    float FrontVecZ = -cosf(Rad);
    VECTOR FrontVector = VGet(FrontVecX, 0.0f, FrontVecZ);
    pGame->GetRadar()->addCenter(position.x, position.z, FrontVector.x, FrontVector.z);
}


/**
* @brief Idle状態の管理メソッド
*/
void Player::Idle()
{
    isMove = false;
    // 移動ベクトルを初期化
    moveVec = VGet(0.f, 0.f, 0.f);

    // アニメーションをセット
    if (animNum != (int)ePlayer::AnimationNum::Idle)  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = (int)ePlayer::AnimationNum::Idle;
        setAnim(animHandle, animNum, animTime, animTimer);
    }
    if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
        animTimer = 0.f;

    if (checkMoveKey()) {
        currentState = PlayerState::Move;
    }
    else if (checkRollKey()) {
        currentState = PlayerState::Roll;
    }
    else if (CheckHitKey(KEY_INPUT_F)) {
        currentState = PlayerState::Healing;
    }
    else if (CheckHitKey(KEY_INPUT_G)) {
        currentState = PlayerState::Death;
    }
}


/**
* @brief Move状態の管理メソッド
* @note  移動キーを話すとIdle
*/
void Player::Move()
{
    if (Key_ForwardMove || PadInput & PAD_INPUT_UP)
    {
        // アニメーション、移動動作をセット
        animateAndMove(ePlayer::AnimationNum::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // アニメーションタイマーリセット
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Down => Runモーション(3) 下移動
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        animateAndMove(ePlayer::AnimationNum::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Right => Runモーション(3) 右移動
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Left => Runモーション(3) 左移動
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    else
    {
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Roll状態の管理メソッド
* @note  アニメーション終了時にIdle    Todo 連続Roll
*/
void Player::Roll()
{
    // Space or PAD_× => Roll
    if (Key_ForwardRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
    }
    // 右Roll
    else if (Key_RightRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
    }
    // 左Roll
    else if (Key_LeftRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
    }

    // アニメーション終了後
    if (rollAble)
    {
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
        {
            animTimer = 0.f;
            rollAble = false;
            currentState = PlayerState::Idle;
        }
    }
}


/**
* @brief Attack状態の管理メソッド
*/
void Player::Attack()
{

}


/**
* @brief Damage状態の管理メソッド
* @norte HPの減少　HP <= 0でDeathへ
*/
void Player::Damage()
{
    if (hitPoint <= 0) {
        currentState = PlayerState::Death;
    }

}


/**
* @brief Healing状態の管理メソッド
* @note  HPの回復　アニメーション終了時にIdle
*/
void Player::Healing()
{
    // F => Drinking 回復時モーション
    if (CheckHitKey(KEY_INPUT_F))
    {
        // アニメーションをセット
        if (animNum != (int)ePlayer::AnimationNum::Drinking)  // ここがないとanimTimerがうまくリセットされない
        {
            animNum = (int)ePlayer::AnimationNum::Drinking;
            setAnim(animHandle, animNum, animTime, animTimer);
        }

    }

    // アニメーション終了後
    if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        animTimer = 0.f;
        // ここでHP回復
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Death状態の管理メソッド
* @note  HPが0でここ　アニメーション終了時、isAliveをfalseにしてゲーム終了 
*/
void Player::Death()
{
    // G => Dying
    if (CheckHitKey(KEY_INPUT_G))
    {
        // アニメーションをセット
        if (animNum != (int)ePlayer::AnimationNum::Dying)  // ここがないとanimTimerがうまくリセットされない
        {
            animNum = (int)ePlayer::AnimationNum::Dying;
            setAnim(animHandle, animNum, animTime, animTimer);
        }

    }

    // アニメーション終了後
    if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        animTimer = 0.f;
    }
}


/**
* @brief  生き死にを結果として返す
* @return true:生存 / false:死亡
*/
bool Player::isAlive()
{
    if (hitPoint <= 0)
    {
        return false;
    }

#ifdef _DEBUG
    // Oでゲーム画面終了
    if (CheckHitKey(KEY_INPUT_O)) { return false; }
    // LでHP減少
    if (CheckHitKey(KEY_INPUT_L)) { hitPoint -= HP_CHANGE_AMOUNT; }
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

#ifdef _DEBUG
    // 当たり判定カプセル描画
    // player
    DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);
    // enemy
    VECTOR EnemyPos = pGame->GetEnemy()->GetPos();
    DrawCapsule3D(EnemyPos, VGet(EnemyPos.x, EnemyPos.y + CAP_HEIGHT, EnemyPos.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
#endif

}


/**
* @brief プレイヤー座標を取得して返す
*/
VECTOR Player::GetPos()
{   
    return position;
}


/**
* @brief Hpを取得して返す
*/
float Player::GetHp()
{
    return hitPoint;
}