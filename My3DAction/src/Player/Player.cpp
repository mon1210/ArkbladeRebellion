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
        animHandle = pGame->GetModelManager()->GetPlayerModel();

    angle = PLAYER_START_ROTATE_Y;

    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, ePlayer::Idle);
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
    if (animNo != num)  // ここがないとanimTimerがうまくリセットされない
    {
        animNo = num;
        setAnim(animHandle, animNo, animTime, animTimer);
    }

    // 移動する向きと速度を設定
    if (animNo == num)
    {
        angle = ROTATE_ANGLE - pGame->GetCamera()->GetHorizontalAngle();
        isMove = true;
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


/**
* @brief 行動管理メソッド
* @note  入力されたキーによって行動判定
*/
// ****************************************** //
// PAD入力　PAD_INPUT_1 = □, PAD_INPUT_2 = ×,
//          PAD_INPUT_3 = 〇, PAD_INPUT_4 = △,
//          PAD_INPUT_5 = L1, PAD_INPUT_6 = R1,
//          PAD_INPUT_7 = L2, PAD_INPUT_8 = R2,
//          PAD INPUT_9 = SHARE(-),
//          PAD INPUT_10 = OPTIONS(+)
// ****************************************** //
void Player::update()
{
    // 移動ベクトルを初期化
    moveVec = VGet(0.f, 0.f, 0.f);

    // Up => Runモーション(3) 前移動
    if (Key_ForwardMove || PadInput & PAD_INPUT_UP)
    {
        // アニメーション、移動動作をセット
        animateAndMove(ePlayer::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // アニメーションタイマーリセット
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Down => Runモーション(3) 下移動
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        animateAndMove(ePlayer::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Right => Runモーション(3) 右移動
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        animateAndMove(ePlayer::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Left => Runモーション(3) 左移動
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        animateAndMove(ePlayer::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Space or PAD_× => Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_W) && rollAble)
    {
        animateAndMove(ePlayer::Roll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // 右Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_D) && rollAble)
    {
        animateAndMove(ePlayer::Roll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // 左Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_A) && rollAble)
    {
        animateAndMove(ePlayer::Roll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // F => Drinking 回復時モーション
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // アニメーションをセット
        if (animNo != ePlayer::Drinking)  // ここがないとanimTimerがうまくリセットされない
        {
            animNo = ePlayer::Drinking;
            setAnim(animHandle, animNo, animTime, animTimer);
        }
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // アニメーションをセット
        if (animNo != ePlayer::Dying)  // ここがないとanimTimerがうまくリセットされない
        {
            animNo = ePlayer::Dying;
            setAnim(animHandle, animNo, animTime, animTimer);
        }
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Idle
    else
    {
        isMove = false;
        // アニメーションをセット
        if (animNo != ePlayer::Idle)  // ここがないとanimTimerがうまくリセットされない
        {
            animNo = ePlayer::Idle;
            setAnim(animHandle, animNo, animTime, animTimer);
        }
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }

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