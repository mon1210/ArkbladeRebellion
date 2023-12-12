#include "Player.h"

/**
* @brief Playerのコンストラクタ
*
*/
Player::Player(Game *parent)
{
    animNo = 0;
    animHandle = 0;
    animTime = 0.f;
    animTimer = 0.f;
    hitPoint = 100.f;
    cameraHA = 0.f;
    pCollision = NULL;
    pRadar = NULL;

    angle = PLAYER_START_ROTATE_Y;

    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    newPos = position;
    moveVec = VGet(0.f, 0.f, 0.f);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    pCollision = parent->GetCollision();
    pRadar = parent->GetRadar();

    moveFlag = false;
    rollAble = true;

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, ePlayer::Idle);
}


/**
* @brief デストラクタ
* @note  ポインタのDeleteはStageでしているので、記述の必要なし
*/
Player::~Player()
{
}


/**
* @brief プレイヤーモデルをセットする
*
*/
void Player::setPlayerModel(int model)
{
    animHandle = model;
}


// Rollだけ、PLAYER_ANIM_F_INCREMENT(== 0.2f)だと違和感があるので、作っている
// また、長押しで回転し続けられるのを直すようにもしたい
// 未完成


/**
* @brief カメラの水平角度をセットする
*
*/
void Player::setCameraHAngle(float camera_H_A)
{
    cameraHA = camera_H_A;
}


/**
* @brief 新座標をセットする
* @note  移動後、新しい座標を取得するため
*/
void Player::setPlayerNewPos(VECTOR new_pos)
{
    newPos = position;  // 現在の位置を取得してから
    newPos = new_pos;
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
void Player::moveHandle(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z)
{
    // アニメーションをセット
    if (animNo != num)  // ここがないとanimTimerがうまくリセットされない
    {
        animNo = num;
        SetAnim(animHandle, animNo, animTime, animTimer);
    }

    // 移動する向きと速度を設定
    if (animNo == num)
    {
        angle = ROTATE_ANGLE - cameraHA;
        moveFlag = true;
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
        moveHandle(ePlayer::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // アニメーションタイマーリセット
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Down => Runモーション(3) 下移動
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        moveHandle(ePlayer::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Right => Runモーション(3) 右移動
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        moveHandle(ePlayer::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Left => Runモーション(3) 左移動
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        moveHandle(ePlayer::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Space or PAD_× => Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_W) && rollAble)
    {
        moveHandle(ePlayer::Roll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // 右Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_D) && rollAble)
    {
        moveHandle(ePlayer::Roll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // 左Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_A) && rollAble)
    {
        moveHandle(ePlayer::Roll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // F => Drinking 回復時モーション
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // angle をセットすることで今の向きを保持
        moveHandle(ePlayer::Drinking, angle, 0, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        moveHandle(ePlayer::Dying, angle, 0, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Idle
    else
    {
        moveFlag = false;
        moveHandle(ePlayer::Idle,angle, 0, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }

    // モデルにタイマーセット
    // これがないとアニメーションしない
    MV1SetAttachAnimTime(animHandle, 0, animTimer);

    // 移動した場合の当たり判定更新と座標セット
    if (moveFlag)
        pCollision->clampToStageBounds(newPos, position, rollAble);

    // Todo プレイヤーの向きに対する動きがいまいち
    // レーダーの中心を今の座標と正面の向きに設定
    float rad = angle * (DX_PI / 180.0f);
    float front_vec_x = -sinf(rad);
    float front_vec_z = -cosf(rad);
    VECTOR frontVector = VGet(front_vec_x, 0.0f, front_vec_z);
    pRadar->addCenter(position.x, position.z, frontVector.x, frontVector.z);
}


/**
* @brief プレイヤーのアニメーションメソッド
* @return true:生存 / false:死亡
*/
bool Player::move()
{
    if (hitPoint <= 0)
    {
        return false;
    }

    // シーン遷移デバッグ用
    if (CheckHitKey(KEY_INPUT_O))return false;

    return true;

}


/**
* @brief 描画メソッド
* @note  プレイヤーを追従するためカメラ用関数はここで呼び出す
*/
void Player::draw()
{
    // モデルの大きさ変更
    MV1SetScale(animHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // モデルの回転
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // 3Dモデルに座標をセット
    MV1SetPosition(animHandle, position);


    //VECTOR rotate = MV1GetRotationXYZ(anim_handle);
    //int nRotateY = static_cast<int>(rotate.y);
    //DrawFormatString(0, 0, GetColor(0, 0, 0), "nRotateY:%d",nRotateY);


    // 
    //pCollider->draw(position, VAdd(position, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)),
    //    CHARA_HIT_WIDTH, 50, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

    // 3Dモデルの描画
    MV1DrawModel(animHandle);

}


/**
* @brief プレイヤー座標を取得して返す
* @note  
*/
VECTOR Player::getPlayerPos()
{   
    return position;
}


/**
* @brief プレイヤー移動ベクトルを取得して返す
* @note
*/
VECTOR Player::getPlayerMoveVec()
{
    return moveVec;
}