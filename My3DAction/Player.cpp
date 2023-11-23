/*
* @file	 Player.cpp
* @brief
*
*
*/
#include "Player.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"


// コンストラクタ
Player::Player(Stage* pParent)
{
    Parent = pParent;
    anim_no = 0;
    anim_time = 0.f;
    anim_timer = 0.f;
    hitPoint = 0.f;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);

    Model modelObject;
    modelObject.ModelSet();
    anim_handle = modelObject.playerHandle;
    
    // ここで処理しても -1 になる
    //anim_handle = MV1LoadModel("res\\Player\\PlayerModel.mv1");

    // 
    MV1AttachAnim(anim_handle, ePlayer::Idle);
    //
    anim_timer = 0.f;
    //
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);

}


// デストラクタ
Player::~Player()
{

}


// 
void Player::Init()
{
    //anim_handle = 0;
    //// 
    //MV1AttachAnim(anim_handle, ePlayer::Idle);
    ////
    //anim_timer = 0.f;
    ////
    //anim_time = MV1GetAnimTotalTime(anim_handle, 0);
}


// 
void Player::SetAnim()
{
    if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_E))
    {
        if (anim_no != ePlayer::Run)
        {
            anim_no = ePlayer::Run;
            anim_timer = 0;
            // アニメーションにかかる時間を取得
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // アニメーションをデタッチ
            MV1DetachAnim(anim_handle, 0);
            // アニメーションをアタッチ
            MV1AttachAnim(anim_handle, anim_no);
            // 
            if (anim_no == ePlayer::Run)
            {
                angle = -135.f;
                position.x += PLAYER_MOVE_SPEED * VECTOR_SCALING;
                position.z += PLAYER_MOVE_SPEED * VECTOR_SCALING;
            }

        }
    }
    // W or UP => Runモーション(3)
    else if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP))
    {
        if (anim_no != ePlayer::Run)
        {
            //PlayerSetAnimation(player_handle, anim_player_time, player_anim_timer, player_anim_no, PlayerAnimationNum:: PRun);
            anim_no = ePlayer::Run;
            anim_timer = 0;
            // アニメーションにかかる時間を取得
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // アニメーションをデタッチ
            MV1DetachAnim(anim_handle, 0);
            // アニメーションをアタッチ
            MV1AttachAnim(anim_handle, anim_no);
            // 前移動
            if (anim_no == ePlayer::Run)
            {
                angle = 180.f;
                position.z += PLAYER_MOVE_SPEED;
            }

        }
    }
    // D => Runモーション(3) 右移動
    else if (CheckHitKey(KEY_INPUT_D))
    {
        if (anim_no != ePlayer::Run)
        {
            anim_no = ePlayer::Run;
            anim_timer = 0;
            // アニメーションにかかる時間を取得
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // アニメーションをデタッチ
            MV1DetachAnim(anim_handle, 0);
            // アニメーションをアタッチ
            MV1AttachAnim(anim_handle, anim_no);
            // 右移動
            if (anim_no == ePlayer::Run)
            {
                angle = -90.f;
                position.x += PLAYER_MOVE_SPEED;
            }
        }
    }
    else
    {
        // アニメーションがないとき、Idleモーション(4)
        if (anim_no != ePlayer::Idle)
        {
            anim_no = ePlayer::Idle;
            anim_timer = 0;
            // アニメーションにかかる時間を取得
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // アニメーションをデタッチ
            MV1DetachAnim(anim_handle, 0);
            // アニメーションをアタッチ
            MV1AttachAnim(anim_handle, anim_no);
        }

    }


}


// 
void Player::Update()
{
    // 
    SetAnim();

    anim_timer += PLAYER_ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (anim_timer >= anim_time)
    {
        anim_time = 0.0f;
    }
    MV1SetAttachAnimTime(anim_handle, 0, anim_timer);


    // 画面に映る位置に3Dモデルを移動
    MV1SetPosition(anim_handle, position);

    // モデルの大きさ変更
    MV1SetScale(anim_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // モデルの回転
    MV1SetRotationXYZ(anim_handle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // ３Ｄモデルの描画
    MV1DrawModel(anim_handle);

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
*/
void Player::draw(ID3D11DeviceContext* pDeviceContext)
{


}

