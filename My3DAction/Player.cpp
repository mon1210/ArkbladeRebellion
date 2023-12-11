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
    animTimer = 0.f;
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


/**
* @brief アニメーションセット関数
*
*/
void Player::setAnim(ePlayer::AnimationNum num)
{
    if (animNo != num)
    {
        animNo = num;
        animTimer = 0;
        // アニメーションにかかる時間を取得
        animTime = MV1GetAnimTotalTime(animHandle, animNo);
        // アニメーションをデタッチ
        MV1DetachAnim(animHandle, 0);
        // アニメーションをアタッチ
        MV1AttachAnim(animHandle, animNo);

    }
        animTimer += PLAYER_ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (animTimer >= animTime)
    {
        animTimer -= animTime;
    }
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
}


// Rollだけ、PLAYER_ANIM_F_INCREMENT(== 0.2f)だと違和感があるので、作っている
// また、長押しで回転し続けられるのを直すようにもしたい
// 未完成
void Player::rollAnim()
{
    // アニメーションをセット
    if (animNo != ePlayer::Roll)
    {
        animNo = ePlayer::Roll;
        animTimer = 0;
        // アニメーションにかかる時間を取得
        animTime = MV1GetAnimTotalTime(animHandle, animNo);
        // アニメーションをデタッチ
        MV1DetachAnim(animHandle, 0);
        // アニメーションをアタッチ
        MV1AttachAnim(animHandle, animNo);

    }
    animTimer += PLAYER_ROLL_ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (animTimer >= animTime)
    {
        animTimer -= animTime;
    }
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
}


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
* @brief 行動管理メソッド
*
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
        // アニメーションをセット
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = FORWARD_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.z = PLAYER_MOVE_SPEED;
        }
    }
    // Down => Runモーション(3) 下移動
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        // アニメーションをセット
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = BACKWARD_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.z = -PLAYER_MOVE_SPEED;
        }
    }
    // Right => Runモーション(3) 右移動
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        // アニメーションをセット
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = RIGHT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = PLAYER_MOVE_SPEED;
        }
    }
    // Left => Runモーション(3) 左移動
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        // アニメーションをセット
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = LEFT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = -PLAYER_MOVE_SPEED;
        }
    }
    // Space or PAD_× => Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_W) && rollAble)
    {
        rollAnim();
        if (animNo == ePlayer::Roll)
        {
            angle = FORWARD_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.z = PLAYER_MOVE_SPEED;
        }
    }
    // 右Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_D) && rollAble)
    {
        rollAnim();
        if (animNo == ePlayer::Roll)
        {
            angle = RIGHT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = PLAYER_MOVE_SPEED;
        }
    }
    // 左Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_A) && rollAble)
    {
        rollAnim();
        if (animNo == ePlayer::Roll)
        {
            angle = LEFT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = -PLAYER_MOVE_SPEED;
        }
    }
    // F => Drinking 回復時モーション
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // アニメーションをセット
        setAnim(ePlayer::Drinking);
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // アニメーションをセット
        setAnim(ePlayer::Dying);
    }
    // Idle
    else
    {
        moveFlag = false;
        setAnim(ePlayer::Idle);
    }

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