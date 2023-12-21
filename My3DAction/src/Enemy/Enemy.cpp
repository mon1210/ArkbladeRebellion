#include <math.h>
#include "Enemy.h"

/**
* @brief Enemyのコンストラクタ
*/
Enemy::Enemy(Game *Game_)
{
    pGame = Game_;

    // モデル取得
    if (pGame) {
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Enemy);
        tileHandle = pGame->GetBG()->GetModelHandle();
    }

    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, (int)eEnemy::AnimationNum::Idle);

    // unordered_map初期化
    initializeStateFunctions();

}


// デストラクタ
Enemy::~Enemy()
{
}


/**
* @brief アニメーション状態初期化関数
* @note  Stageで初期化時一度だけ呼び出す
*/
void Enemy::initAnimation()
{
    setAnimationHandle(eEnemy::AnimationNum::Idle);

}


/**
* @brief アニメーションを設定する
* @param[in] num    アニメーション番号
*/
void Enemy::setAnimationHandle(eEnemy::AnimationNum num) {
    // アニメーションをセット
    if (animNum != static_cast<int>(num))  // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(num);
        setAnim(animHandle, animNum, animTime, animTimer);
    }
};


/**
* @brief enemyToPlayerの更新・長さを算出　毎フレーム呼び出す
* @note  毎フレームの処理
*/
void Enemy::updateToPlayerVec() 
{
    toPlayerVec = VSub(pGame->GetPlayer()->GetPos(), position);   // エネミーからプレイヤーの距離ベクトルを求める
    vecLength = sqrtf(toPlayerVec.x * toPlayerVec.x + toPlayerVec.z * toPlayerVec.z); // 距離ベクトルの長さ
}


/**
* @brief unordered_map初期化メソッド
* @note  各Stateごとのメソッドを登録
*/
void Enemy::initializeStateFunctions()
{
    stateFunctionMap[EnemyState::Wait]  = [this]() { Wait();  };
    stateFunctionMap[EnemyState::Move]  = [this]() { Move();  };
    stateFunctionMap[EnemyState::Chase] = [this]() { Chase(); };
    //stateFunctionMap[EnemyState::Attack] = [this]() { Attack();  };
    //stateFunctionMap[EnemyState::Damage] = [this]() { Damage();  };  
    //stateFunctionMap[EnemyState::Death] = [this]() { Death();   };

}


/**
* @brief 行動状態の管理メソッド
* @note  毎フレームの処理
*/
void Enemy::update()
{
    // 今のStateに対応するメソッド呼び出し
    stateFunctionMap[currentState]();

    // enemyとplayerの距離ベクトルの更新
    updateToPlayerVec();

    // RaderのPointに追加
    pGame->GetRadar()->addPoint(position.x, position.z, eRadar::PointType::Enemy);

    // アニメーションタイマーリセット
    if (updateAnimation(animTime, animTimer, ENEMY_ANIM_F_INCREMENT))
        animTimer = 0.f;

}


/**
* @brief Wait状態の管理メソッド
*/
void Enemy::Wait()
{
    // 行動 => 何もしない
    //SetAnim(eEnemy::Idle);  // これがないとanimTimerが増加せず、最初固まる

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
        angle = (rand() % FULL_CIRCLE_DEGREES);  // ランダムな角度を取得
        // アニメーションをセット
        setAnimationHandle(eEnemy::AnimationNum::Run);

    }
    // 視野に入っていたら追跡
    else if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // アニメーションをセット
        setAnimationHandle(eEnemy::AnimationNum::Run);
    }

}


/**
* @brief Move状態の管理メソッド
*/
void Enemy::Move()
{
    // 行動：まっすぐ進む(ステージ上の時)
    // ベクトル算出
    float Rad = angle * DX_PI_F / 180.f;
    // 三次元ベクトルの生成
    VECTOR Vec = VGet(sinf(Rad), 0.f, cosf(Rad));
    // -1を乗算することでベクトルが逆転
    Vec = VScale(Vec, -1.f);

    // 座標変更
    // ベクトルの大きさを乗算、移動速度に
    Vec = VScale(Vec, ENEMY_MOVE_SPEED);
    // 移動先までのベクトル取得
    VECTOR NewPos = VAdd(Vec, position);

    NewPos.y += 1.0f;  // これがないと左右,下に移動できない
    // MV1_COLL_RESULT_POLY => 当たり判定の結果情報が保存された構造体
    MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(
        tileHandle,				                             // 判定対象となるモデルのフレーム
        -1,												        // 対象となるフレーム番号
        NewPos,										        // Rayの始点   モデルの足元
        VGet(NewPos.x, NewPos.y - CHARA_HEIGHT, NewPos.z)	// Rayの終点   モデルの頭上
    );

    if (Result.HitFlag == 1) // 当たりチェック
    {
        // HitPosition => 交点の座標
        NewPos.y = Result.HitPosition.y;
        position = NewPos;
        if (isTargetVisible() == true)
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
        // アニメーションをセット
        setAnimationHandle(eEnemy::AnimationNum::Idle);
    }
    // 視野に入っていたら追跡
    else if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // アニメーションはすでにRunなので変更なし
    }

}


/**
* @brief Chase状態の管理メソッド
*/
void Enemy::Chase()
{
    // 行動：視野内のプレイヤーを追いかける
    
    // 距離が0以下の時は何もしない   // ほぼ通らない
    if (vecLength <= 0.f) { return; }

    // ベクトルを単位ベクトルに
    VECTOR Direction = VGet(toPlayerVec.x / vecLength, 0.f, toPlayerVec.z / vecLength);

    // 単位ベクトルをスカラー倍、移動速度に
    VECTOR Velocity = VScale(Direction, ENEMY_MOVE_SPEED);

    // 移動先までのベクトル取得
    VECTOR NewPos = VAdd(Velocity, position);

    //VECTOR playerPos = pGame->GetPlayer()->getPos();
    //pGame->GetCollision()->charaCapCol(position, new_pos, playerPos, CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS);

    NewPos.y += 1.0f;  // これがないと左右,下に移動できない
    // MV1_COLL_RESULT_POLY => 当たり判定の結果情報が保存された構造体
    MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(
        tileHandle,				                                // 判定対象となるモデルのフレーム
        -1,												        // 対象となるフレーム番号
        NewPos,										        // Rayの始点   モデルの足元
        VGet(NewPos.x, NewPos.y - CHARA_HEIGHT, NewPos.z)	// Rayの終点   モデルの頭上
    );

    if (Result.HitFlag == 1) // 当たりチェック
    {
        // HitPosition => 交点の座標
        NewPos.y = Result.HitPosition.y;
        // if(length >= ENEMY_SPEED)
        position = NewPos;
    }

    // 逆三角関数を使用　ベクトルからエネミーに対するプレイヤーの角度を求める
    angle = atan2f(-Velocity.x, -Velocity.z);

    // 遷移
    /*
        待機：
            条件：プレイヤーが視野から出る
    */
    if (isTargetVisible() == false)
    {
        currentState = EnemyState::Wait;
        count = 0;
        setAnimationHandle(eEnemy::AnimationNum::Idle);
    }
}


/**
* @brief   エネミーの視野メソッド
* @return  true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる 
*/
bool Enemy::isTargetVisible()
{
    /*
        ・Enemyの座標(x,z)を円の中心として考える
        ・Playerの座標を点として考える
        ・円の半径は10

        点と円の当たり判定を使い、点が円の中にあったらtrue
    
    */
    // 円の半径よりベクトルが短くなったらtrueを返す
    if (vecLength <= ENEMY_VIEW_RADIUS)
    {
        return true;
    }
    
    return false;
}


/**
* @brief  生き死にを結果として返す
* @return true:生存 / false:死亡
*/
bool Enemy::isAlive()
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
    // モデルにタイマーセット
    // これがないとアニメーションしない
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
* @brief エネミー座標を取得して返す
*/
VECTOR Enemy::GetPos()
{
    return  position;
}