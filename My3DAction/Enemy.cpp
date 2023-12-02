#include "Enemy.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"


/**
* @brief Enemyのコンストラクタ
*
*/
Enemy::Enemy()
{
    animNo = 0;
    animTime = 0.f;
    animTimer = 0.f;
    hitPoint = 1.f;
    animTimer = 0.f;
    pModel = NULL;
    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    pModel = new Model();

    // モデル取得
    pModel->LoadEnemyModel();
    animHandle = pModel->GetEnemyModel();

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, eEnemy::Idle);


}


// デストラクタ
Enemy::~Enemy()
{
    SAFE_DELETE(pModel);
}


/**
* @brief アニメーションセット関数
*
*/
void Enemy::SetAnim(eEnemy::AnimationNum num)
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

}


/**
* @brief 行動管理関数
* @Todo  行動をランダムにしたいので後で消す
*/
void Enemy::SetMove()
{
    // I => Runモーション(2)
    if (CheckHitKey(KEY_INPUT_K))
    {
        SetAnim(eEnemy::Run);
        // 手前移動
        if (animNo == eEnemy::Run)
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
        if (animNo == eEnemy::Run)
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
    // 行動管理関数呼び出し
    SetMove();

    animTimer += ENEMY_ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (animTimer >= animTime)
    {
        animTimer = 0.0f;
    }
    MV1SetAttachAnimTime(animHandle, 0, animTimer);


    // 画面に映る位置に3Dモデルを移動
    MV1SetPosition(animHandle, position);

    // モデルの大きさ変更
    MV1SetScale(animHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // モデルの回転
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // ３Ｄモデルの描画
    MV1DrawModel(animHandle);

}


/**
* @brief エネミー座標取得用関数
* @note
*/
VECTOR Enemy::GetEnemyPos()
{
    return  position;
}