#include <math.h>
#include "Enemy.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"
#include "BG.h"
#include "Player.h"


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
    pBG = NULL;
    pPlayer = NULL;
    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    currentState = EnemyState::Wait;

    pBG = new BG();
    pModel = new Model();
    pPlayer = new Player();
    // モデル取得
    pModel->LoadEnemyModel();
    animHandle = pModel->GetEnemyModel();

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, eEnemy::Idle);


}


// デストラクタ
Enemy::~Enemy()
{
    SAFE_DELETE(pBG);
    SAFE_DELETE(pPlayer);
    SAFE_DELETE(pModel);
}


/**
* @brief アニメーション状態初期化関数
* @note  My3DAction.cppで一回だけ呼び出す
*/
void Enemy::InitAnimation()
{
    SetAnim(eEnemy::Idle);
}


/**
* @brief 行動状態の管理メソッド
* @note  毎フレームの処理
*/
void Enemy::Update()
{
    switch (currentState)
    {
    case EnemyState::Wait:
        Wait();
        break;
    case EnemyState::Move:
        Move();
        break;
    case EnemyState::Chase:
        Chase();
        break;
    //case EnemyState::Attack:
    //    break;
    //case EnemyState::Damage:
    //    break;
    //case EnemyState::Death:
    //    break;
    }

    // Rader


    // 描画メソッド呼び出し
    draw();
}


/**
* @brief Wait状態の管理メソッド
* 
*/
void Enemy::Wait()
{
    // 行動 => 何もしない
    SetAnim(eEnemy::Idle);  // これがないとanimTimerが増加せず、最初固まる

    // 遷移
    /*
        移動：
            条件：一定時間の経過
        追跡：
            条件：視野にプレイヤーが入る
    */
    count++;

    if (count > TIME_TO_TRANSITION)   // 遷移タイマーを超えたのでMoveへ
    {
        count = 0;
        currentState = EnemyState::Move;
        angle = (rand() % 360);  // ランダムな角度を取得
        SetAnim(eEnemy::Run);

    }
    // 視野に入っていたら追跡
    else if (IsTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        SetAnim(eEnemy::Run);
    }

}


// 
void Enemy::Move()
{
    // 行動：まっすぐ進む(ステージ上の時)
    // ベクトル算出
    float rad = angle * DX_PI_F / 180.f;
    // 三次元ベクトルの生成
    VECTOR vec = VGet(sinf(rad), 0.f, cosf(rad));
    // -1を乗算することでベクトルが逆転
    vec = VScale(vec, -1.f);

    // 座標変更
    //float move_speed = 0.1f;
    // ベクトルの大きさを乗算、移動速度に
    vec = VScale(vec, ENEMY_MOVE_SPEED);
    // 移動先までのベクトル取得
    VECTOR new_pos = VAdd(vec, position);

    new_pos.y += 1.0f;  // これがないと左右,下に移動できない
    // MV1_COLL_RESULT_POLY => 当たり判定の結果情報が保存された構造体
    MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
        pBG->GetModelHandle(),				    // 判定対象となるモデルのフレーム
        -1,												// 対象となるフレーム番号
        new_pos,										// Rayの始点   モデルの足元
        VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Rayの終点   モデルの頭上
    );

    if (result.HitFlag == 1) // 当たりチェック
    {
        // HitPosition => 交点の座標
        new_pos.y = result.HitPosition.y;
        position = new_pos;
        if (IsTargetVisible() == true)
        {
            currentState = EnemyState::Chase;
        }
    }

    // 遷移
    /*
        待機：
            条件：一定時間の経過
        追跡：
            条件：視野にプレイヤーが入る
    */
    count++;

    if (count >= TIME_TO_TRANSITION)     // 遷移タイマーを超えたのでWaitへ
    {
        count = 0;
        currentState = EnemyState::Wait;
        SetAnim(eEnemy::Idle);
    }
    // 視野に入っていたら追跡
    else if (IsTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // アニメーションはすでにRunなので変更なし
    }

}


// 
void Enemy::Chase()
{
    // 行動：視野内のプレイヤーを追いかける
    // エネミーからプレイヤーのベクトル(x,zのみ)を算出
    // VECTOR player_pos = *pPlayer->GetPlayerPos();
    VECTOR enemy_to_player = VSub(/*player_pos*/*pPlayer->GetPlayerPos(), position);

    // ベクトルの長さを算出
    float length = sqrt(enemy_to_player.x * enemy_to_player.x + enemy_to_player.z * enemy_to_player.z);
    // 距離が0以下の時は何もしない
    if (length <= 0.f) { return; }

    // ベクトルを単位ベクトルに
    VECTOR direction = VGet(enemy_to_player.x / length, 0.f, enemy_to_player.z / length);

    // 単位ベクトルをスカラー倍、移動速度に
    VECTOR velocity = VScale(direction, ENEMY_MOVE_SPEED);

    VECTOR new_pos = VAdd(velocity, position);
    new_pos.y += 1.0f;  // これがないと左右,下に移動できない
    // MV1_COLL_RESULT_POLY => 当たり判定の結果情報が保存された構造体
    MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
        pBG->GetModelHandle(),				    // 判定対象となるモデルのフレーム
        -1,												// 対象となるフレーム番号
        new_pos,										// Rayの始点   モデルの足元
        VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Rayの終点   モデルの頭上
    );

    if (result.HitFlag == 1) // 当たりチェック
    {
        // HitPosition => 交点の座標
        new_pos.y = result.HitPosition.y;
        position = new_pos;
    }

    // 逆三角関数を使用　ベクトルからエネミーに対するプレイヤーの角度を求める
    angle = atan2f(-velocity.x, -velocity.z);

    // 遷移
    /*
        待機：
            条件：プレイヤーが視野から出る
    */
    if (IsTargetVisible() == false)
    {
        currentState = EnemyState::Wait;
        count = 0;
        SetAnim(eEnemy::Idle);
    }
}


// 
bool Enemy::IsTargetVisible()
{
    /*
        ・Enemyの座標(x,z)を円の中心として考える
        ・Playerの座標を点として考える
        ・円の半径は10

        点と円の当たり判定を使い、点が円の中にあったらtrue
    
    */

    VECTOR vec = VSub(*pPlayer->GetPlayerPos(), position);   // エネミーからプレイヤーの距離ベクトル
    float length = sqrtf(vec.x * vec.x + vec.z * vec.z);    // 距離ベクトルの長さ

    float radius = 500.f;    // 円の半径

    // 半径よりベクトルが短くなったらtrueを返す
    if (length <= radius)
    {
        return true;
    }
    
    return false;
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
    //SetMove();

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