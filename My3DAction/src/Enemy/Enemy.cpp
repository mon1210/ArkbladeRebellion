#include <math.h>
#include "Enemy.h"

/**
* @brief Enemyのコンストラクタ
*/
Enemy::Enemy(Game *Game_)
{
    pGame = Game_;

    // モデル取得
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Enemy);

}


// デストラクタ
Enemy::~Enemy()
{
    delete[] animTimes;
}


/**
* @brief 初期化メソッド
* @note
*/
void Enemy::initialize(int hit_point)
{
    // 変数初期化
    hitPoint = hit_point;
    currentHP = hitPoint;
    angle = ENEMY_START_ROTATE_Y;
    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    count = 0;
    toPlayerVec = VGet(0.f, 0.f, 0.f);

    // モデルにIdleアニメーションをセット
    MV1AttachAnim(animHandle, (int)eEnemy::AnimationNum::Idle);

    // unordered_map初期化
    initializeStateFunctions();

    // animTimesのサイズをanimationListと同じサイズに
    animTimes = new float[static_cast<int>(eEnemy::AnimationNum::Dying) + 1];
    // animTimesにアニメーション時間を保存
    for (int i = static_cast<int>(eEnemy::AnimationNum::Idle); i <= static_cast<int>(eEnemy::AnimationNum::Dying); i++)
    {
        animTimes[i] = MV1GetAnimTotalTime(animHandle, i);
    }

    // アニメーション状態初期化
    setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);

    // アニメーションタイマーリセット
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


/**
* @brief enemyToPlayerの更新・長さを算出　毎フレーム呼び出す
* @note  毎フレームの処理
*/
void Enemy::updateToPlayerVec()
{
    toPlayerVec = VSub(pGame->GetPlayer()->GetPos(), position);                         // エネミーからプレイヤーの距離ベクトルを求める
    vecLength = sqrtf(toPlayerVec.x * toPlayerVec.x + toPlayerVec.z * toPlayerVec.z);   // 距離ベクトルの長さ
}


/**
* @brief unordered_map初期化メソッド
* @note  各Stateごとのメソッドを登録
*/
void Enemy::initializeStateFunctions()
{
    stateFunctionMap[EnemyState::Wait]      = [this]() { wait();   };
    stateFunctionMap[EnemyState::Move]      = [this]() { move();   };
    stateFunctionMap[EnemyState::Chase]     = [this]() { chase();  };
    stateFunctionMap[EnemyState::Attack]    = [this]() { attack(); };
    stateFunctionMap[EnemyState::Damage]    = [this]() { damage(); };  
    stateFunctionMap[EnemyState::Death]     = [this]() { death();  };

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
}


/**
* @brief 状態とアニメーションを設定
* @note  状態変更時に使用
* @param[in] state  変更先の状態
* @param[in] num    変更先のアニメーション
*/
void Enemy::setStateAndAnim(EnemyState state, eEnemy::AnimationNum anim_num)
{
    // カウントリセット
    count = 0;
    // State変更
    currentState = state;

    // アニメーションをセット    
    if (animNum != static_cast<int>(anim_num))   // ここがないとanimTimerがうまくリセットされない
    {
        animNum = static_cast<int>(anim_num);
        setAnim(animHandle, animNum, animTimer);
    }

    // 現在のアニメーションの再生時間を取得
    animTime = animTimes[static_cast<int>(anim_num)];
}


// 以下状態管理メソッド ===============================================================================================
/**
* @brief Wait状態の管理メソッド
*/
void Enemy::wait()
{
    // 行動：何もしない

    // 遷移
    /*
        移動：
            条件：一定時間の経過
        追跡：
            条件：視野にプレイヤーが入る
        攻撃：
            条件：攻撃範囲内にプレイヤーがいる
    */
    count++;

    if (count > TIME_TO_TRANSITION)   // 遷移タイマーを超えた
    {
        // 視野に入っていたら追跡
        if (isTargetVisible() == true)
            setStateAndAnim(EnemyState::Chase, eEnemy::AnimationNum::Run);
        // Moveへ
        else
        {
            angle = (rand() % FULL_CIRCLE_DEGREES);  // ランダムな角度を取得
            setStateAndAnim(EnemyState::Move, eEnemy::AnimationNum::Run);
        }

        // 攻撃フラグOFF
        isAttack = false;
    }

    // 攻撃範囲内にプレイヤーがいたら
    if (pGame->GetCollision()->checkAttackArea(position, pGame->GetPlayer()->GetPos(), 250) && !isAttack)
    {
        setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
        isAttack = true;
    }

    // HP減少時　Damageへ    HPが0以下の際には通らずDeathへ
    if (hitPoint < currentHP && hitPoint > 0) {
        currentState = EnemyState::Damage;
    }

    // アニメーションタイマーリセット
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


/**
* @brief Move状態の管理メソッド
*/
void Enemy::move()
{
    // 行動：まっすぐ進む(ステージ上の時)
    // ベクトル算出
    float Rad = angle * DX_PI_F / 180.f;
    // 三次元ベクトルの生成
    moveVec = VGet(sinf(Rad), 0.f, cosf(Rad));
    // -1を乗算することでベクトルが逆転
    moveVec = VScale(moveVec, -1.f);

    // 座標変更
    // ベクトルの大きさを乗算、移動速度に
    moveVec = VScale(moveVec, ENEMY_MOVE_SPEED);

    // プレイヤーとの当たり判定
    pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS);

    // 移動先までのベクトル取得
    VECTOR NewPos = VAdd(moveVec, position);

    // 床との当たり判定　当たっていたら入る
    if (pGame->GetCollision()->clampToStageBounds(NewPos, position))
    {
        // 視野に入っていたら追跡        
        if (isTargetVisible() == true)
        {
            currentState = EnemyState::Chase;
        }
    }

    // 遷移：
    /*
        待機：
            条件：一定時間の経過
                        　or
                  一定時間の経過　且つ　ランダムな数が0
        追跡：
            条件：視野にプレイヤーが入る
        攻撃：
            条件：攻撃範囲内にプレイヤーがいる
                        　or
                  一定時間の経過　且つ　ランダムな数が1
    */
    count++;

    if (count >= TIME_TO_TRANSITION)     // 遷移タイマーを超えたので状態遷移
    {
        // 0 or 1 ランダムな変数取得
        int RandomStateIndex = rand() % 2;
        switch (RandomStateIndex)
        {
            case 0: // Idleへ
                setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);
                break;
            case 1: // Attackへ
                setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
                isAttack = true;
                break;
        }
    }
    // 視野に入っていたら追跡
    if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // アニメーションはすでにRunなので変更なし
    }

    // 攻撃範囲内にプレイヤーがいたら
    if (pGame->GetCollision()->checkAttackArea(position, pGame->GetPlayer()->GetPos(), 250) && !isAttack)
    {
        setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
        isAttack = true;
    }

    // アニメーションタイマーリセット
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);

}


/**
* @brief Chase状態の管理メソッド
*/
void Enemy::chase()
{
    // 行動：視野内のプレイヤーを追いかける

    // 距離が0以下の時は何もしない   // ほぼ通らない
    if (vecLength <= 0.f) { return; }

    // ベクトルを単位ベクトルに
    VECTOR Direction = VGet(toPlayerVec.x / vecLength, 0.f, toPlayerVec.z / vecLength);

    // 単位ベクトルをスカラー倍、移動速度に
    moveVec = VScale(Direction, ENEMY_MOVE_SPEED);
    // 逆三角関数を使用　ベクトルからエネミーに対するプレイヤーの角度を求める
    /* ※これより下に書くと、接触時に角度が変わってしまうので注意※ */
    angle = atan2f(-moveVec.x, -moveVec.z) * 180.f / DX_PI_F;

    // プレイヤーとの当たり判定
    if (pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS))
        isColHit = true;

    // 移動先までのベクトル取得
    VECTOR NewPos = VAdd(moveVec, position);

    // 床との当たり判定
    pGame->GetCollision()->clampToStageBounds(NewPos, position);

    // 遷移
    /*
        待機：
            条件：プレイヤーが視野から出る
                        　or
                  プレイヤーと当たる
        攻撃：
            条件：攻撃範囲内にプレイヤーがいる
    */
    if (isTargetVisible() == false || isColHit)
    {
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);
        isColHit = false;
    }

    // 攻撃範囲内にプレイヤーがいたら
    if (pGame->GetCollision()->checkAttackArea(position, pGame->GetPlayer()->GetPos(), 250) && !isAttack)
    {
        setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
        isAttack = true;
    }

    // アニメーションタイマーリセット
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


/**
* @brief Attack状態の管理メソッド
*/
void Enemy::attack()
{
    // 行動：攻撃
    DrawString(0, 0, "Attack", RED);// Debug

    // 遷移
    /*
        待機：
            条件：アニメーションの終了
    */
    // アニメーションタイマーリセット
    if (updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT))
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);
}


/**
* @brief Damage状態の管理メソッド
*/
void Enemy::damage()
{    
    // 現在のHP更新
    currentHP = hitPoint;
    // アニメーションをセット
    setStateAndAnim(EnemyState::Damage, eEnemy::AnimationNum::Damage);
    // アニメーション終了後
    if (updateAnimation(animTimes[static_cast<int>(eEnemy::AnimationNum::Damage)], &animTimer, ENEMY_ANIM_F_INCREMENT))
        currentState = EnemyState::Wait;
}


/**
* @brief Death状態の管理メソッド
*/
void Enemy::death()
{
    // アニメーションをセット
    setStateAndAnim(EnemyState::Death, eEnemy::AnimationNum::Dying);
    // アニメーション再生 =======================
    animTimer += ENEMY_ANIM_F_INCREMENT;
    // 死亡時はanimTimerをリセットしないのでここで処理     アニメーション終了時にflagON
    if (animTimer >= animTimes[static_cast<int>(eEnemy::AnimationNum::Dying)])
        isDeath = true;
}
// 以上状態管理メソッド ===============================================================================================


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
    // hitPointが0以下
    if (hitPoint <= 0.f)
    {
        if (isDeath)
        {
            return false;
        }
        // 先に入る
        else
        {
            // 死亡状態へ
            currentState = EnemyState::Death;
        }
    }
#ifdef _DEBUG
    // LでHP減少
    if (CheckHitKey(KEY_INPUT_U)) {
        hitPoint = clamp(hitPoint, 0, MAX_HP); // 最大最小を決定
        hitPoint -= HP_CHANGE_AMOUNT;
    }
#endif

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

#ifdef _DEBUG
    // 当たり判定カプセル描画
    DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
#endif
}
