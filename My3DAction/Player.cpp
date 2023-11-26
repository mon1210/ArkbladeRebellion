
#include "Player.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"
#include "camera.h"


/**
* @brief Playerのコンストラクタ
*
*/
Player::Player()
{
    anim_no = 0;
    anim_time = 0.f;
    anim_timer = 0.f;
    hitPoint = 100.f;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    anim_timer = 0.f;
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);
    pCamera = new Camera();
    moveFlag = false;
    rollFlag = false;

    // インスタンス化生成
    Model modelObject;
    // モデルセット関数呼び出し
    modelObject.PlayerLoadModel();
    anim_handle = modelObject.playerHandle;

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(anim_handle, ePlayer::Idle);
}


// デストラクタ
Player::~Player()
{

}


/**
* @brief アニメーションセット関数
*
*/
void Player::SetAnim(ePlayer::AnimationNum num)
{
    if (anim_no != num)
    {
        anim_no = num;
        anim_timer = 0;
        // アニメーションにかかる時間を取得
        anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
        // アニメーションをデタッチ
        MV1DetachAnim(anim_handle, 0);
        // アニメーションをアタッチ
        MV1AttachAnim(anim_handle, anim_no);

    }
        anim_timer += PLAYER_ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (anim_timer >= anim_time)
    {
        anim_timer -= anim_time;
    }
    MV1SetAttachAnimTime(anim_handle, 0, anim_timer);
}


/**
* @brief 行動管理関数
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
void Player::SetMove()
{
    // カメラ操作関数呼び出し
    pCamera->CameraController();

    // 移動ベクトルを初期化
    moveVec = VGet(0.f, 0.f, 0.f);

    // Up => Runモーション(3) 前移動
    if (CheckHitKey(KEY_INPUT_UP) || PadInput & PAD_INPUT_UP)
    {
        // アニメーションをセット
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = 180.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.z = PLAYER_MOVE_SPEED;
        }
    }
    // Down => Runモーション(3) 下移動
    else if (CheckHitKey(KEY_INPUT_DOWN) || PadInput & PAD_INPUT_DOWN)
    {
        // アニメーションをセット
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = 0.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.z = -PLAYER_MOVE_SPEED;
        }
    }
    // Right => Runモーション(3) 右移動
    else if (CheckHitKey(KEY_INPUT_RIGHT) || PadInput & PAD_INPUT_RIGHT)
    {
        // アニメーションをセット
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = -90.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.x = PLAYER_MOVE_SPEED;
        }
    }
    // Left => Runモーション(3) 左移動
    else if (CheckHitKey(KEY_INPUT_LEFT) || PadInput & PAD_INPUT_LEFT)
    {
        // アニメーションをセット
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = 90.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.x = -PLAYER_MOVE_SPEED;
        }
    }
    // Space or PAD_× => Roll
    else if (CheckHitKey(KEY_INPUT_SPACE) || PadInput & PAD_INPUT_2)
    {
        // アニメーションをセット
        if (anim_no != ePlayer::Roll)
        {
            anim_no = ePlayer::Roll;
            anim_timer = 0;
            // アニメーションにかかる時間を取得
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // アニメーションをデタッチ
            MV1DetachAnim(anim_handle, 0);
            // アニメーションをアタッチ
            MV1AttachAnim(anim_handle, anim_no);

        }
        anim_timer += PLAYER_ROLL_ANIM_F_INCREMENT;
        // アニメーション時間を過ぎたらリセット
        if (anim_timer >= anim_time)
        {
            anim_timer -= anim_time;
        }
        MV1SetAttachAnimTime(anim_handle, 0, anim_timer);

        if (anim_no == ePlayer::Roll)
        {
            moveFlag = true;
            if (angle == 180.f)
                moveVec.z = PLAYER_ROLL_DISTANCE;
            else if (angle == 0.f)
                moveVec.z = -PLAYER_ROLL_DISTANCE;
            else if (angle == -90.f)
                moveVec.x = PLAYER_ROLL_DISTANCE;
            else if (angle == 90.f)
                moveVec.x = -PLAYER_ROLL_DISTANCE;
        }
    }
    // F => Drinking 回復時モーション
    else if (CheckHitKey(KEY_INPUT_F) || PadInput & PAD_INPUT_1)
    {
        // アニメーションをセット
        SetAnim(ePlayer::Drinking);
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // アニメーションをセット
        SetAnim(ePlayer::Dying);
    }
    // Idle
    else
    {
        moveFlag = false;
        SetAnim(ePlayer::Idle);
    }


}


/**
* @brief プレイヤーのアニメーションメソッド
* @return true:生存 / false:死亡
* @note ここでは加速度の設定だけ行い、(x, y)座標の更新はcollide() で行う
*/
bool Player::move()
{
    if (hitPoint <= 0)
    {
        return false;
    }

    return true;

}


/**
* @brief 描画メソッド
* @note  プレイヤーを追従するためカメラ用関数はここで呼び出す
*/
void Player::draw()
{
    // 行動管理関数呼び出し
    SetMove();

    // モデルの大きさ変更
    MV1SetScale(anim_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // モデルの回転
    MV1SetRotationXYZ(anim_handle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // 移動した場合、座標取得
    if (moveFlag)
        position = pCamera->MoveAlongHAngle(moveVec, position);

    // 3Dモデルに座標をセット
    MV1SetPosition(anim_handle, position);

    // カメラの位置と向きを設定
    pCamera->SetCameraPositionAndDirection(position);

    // ３Ｄモデルの描画
    MV1DrawModel(anim_handle);

}

