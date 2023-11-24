/*
* @file	 Enemy.cpp
* @brief
*
*
*/
#include "Enemy.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"


// コンストラクタ
Enemy::Enemy(Stage* pParent)
{
    Parent = pParent;
    anim_no = 0;
    anim_time = 0.f;
    anim_timer = 0.f;
    hitPoint = 1.f;
    angle = ENEMY_START_ROTATE_Y;
    position = VGet(ENEMY_POS_X, ENEMY_POS_Y, ENEMY_POS_Z);

    // インスタンス化生成
    Model modelObject;
    // モデルセット関数呼び出し
    modelObject.EnemyLoadModel();
    anim_handle = modelObject.enemyHandle;

    // 
    MV1AttachAnim(anim_handle, eEnemy::Idle);
    //
    anim_timer = 0.f;
    //
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);

}


// デストラクタ
Enemy::~Enemy()
{

}


// 
void Enemy::Init()
{

}

// 
void Enemy::SetAnim(eEnemy::AnimationNum num)
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

}


// 
void Enemy::SetMove()
{
    // I => Runモーション(2)
    if (CheckHitKey(KEY_INPUT_K))
    {
        SetAnim(eEnemy::Run);
        // 手前移動
        if (anim_no == eEnemy::Run)
        {
            angle = 0.f;
            position.z -= ENEMY_MOVE_SPEED;
        }
    }
    // 
    else if (CheckHitKey(KEY_INPUT_I))
    {
        SetAnim(eEnemy::Run);
        // 手前移動
        if (anim_no == eEnemy::Run)
        {
            angle = 180.f;
            position.z += ENEMY_MOVE_SPEED;
        }
    }
    // 
    else if (CheckHitKey(KEY_INPUT_O))
    {
        SetAnim(eEnemy::Swiping);
    }
    // 
    else if (CheckHitKey(KEY_INPUT_P))
    {
        SetAnim(eEnemy::Damage);
    }
    // 
    else if (CheckHitKey(KEY_INPUT_M))
    {
        SetAnim(eEnemy::Dying);
    }
    else
    {
        SetAnim(eEnemy::Idle);
    }

}


// 
void Enemy::Update()
{
  
}


/**
* @brief エネミーのアニメーションメソッド
* @return true:生存 / false:死亡
* @note ここでは加速度の設定だけ行い、(x, y)座標の更新はcollide() で行う
*/
bool Enemy::move()
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
void Enemy::draw()
{
    // 
    SetMove();

    anim_timer += ENEMY_ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (anim_timer >= anim_time)
    {
        anim_timer = 0.0f;
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