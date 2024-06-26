#include <math.h>
#include "Enemy.h"


// コンストラクタ
Enemy::Enemy(Game *Game)
{
    pGame = Game;

    // モデル取得
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Enemy);

}


// デストラクタ
Enemy::~Enemy()
{
    SAFE_DELETE_ARRAY(animTimes);
}


// 初期化メソッド
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
    MV1AttachAnim(animHandle, static_cast<int>(eEnemy::AnimationNum::Idle));

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


// enemyToPlayerの更新・長さを算出
void Enemy::updateToPlayerVec()
{
    toPlayerVec = VSub(pGame->GetPlayer()->GetPos(), position);                         // エネミーからプレイヤーの距離ベクトルを求める
    vecLength = sqrtf(toPlayerVec.x * toPlayerVec.x + toPlayerVec.z * toPlayerVec.z);   // 距離ベクトルの長さ
}


// unordered_map初期化
void Enemy::initializeStateFunctions()
{
    stateFunctionMap[EnemyState::Wait]      = [this]() { wait();   };
    stateFunctionMap[EnemyState::Move]      = [this]() { move();   };
    stateFunctionMap[EnemyState::Chase]     = [this]() { chase();  };
    stateFunctionMap[EnemyState::Attack]    = [this]() { attack(); };
    stateFunctionMap[EnemyState::Damage]    = [this]() { damage(); };
    stateFunctionMap[EnemyState::Death]     = [this]() { death();  };

}


// 行動状態の管理
void Enemy::update()
{
    // 今のStateに対応するメソッド呼び出し
    stateFunctionMap[currentState]();

    // hitPoint0以下でdeathへ
    if (hitPoint <= 0 && !isDeath)
        currentState = EnemyState::Death;

    // enemyとplayerの距離ベクトルの更新
    updateToPlayerVec();

    // RaderのPointに追加
    pGame->GetRadar()->addPoint(position.x, position.z, eRadar::PointType::Enemy);

    // 攻撃を受けた時
    if (pGame->GetPlayer()->GetIsHitFlag())
    {
        hitPoint = clamp(hitPoint -= PLAYER_ATTACK, 0, ENEMY_MAX_HP); // 最大最小を決定
    }
}


// 状態とアニメーションを設定
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


// 移動後の座標を設定
void Enemy::moveHandle()
{
    // モデルの座標・向きをもとに値設定
    VECTOR ObbAngle = VGet(0.f, angle, 0.f);
    VECTOR ObbTrans = VGet(position.x, position.y + ENEMY_OBB_TRANS_Y, position.z);

    // OBB値変更
    mOBBCol.changeRotateMatrix(ObbAngle);      // 回転
    mOBBCol.changeTranslateMatrix(ObbTrans);   // 移動

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
}


// 以下状態管理メソッド ===============================================================================================
// Wait状態の管理
void Enemy::wait()
{
    // 行動：何もしない
    // 攻撃ヒットフラグを折る
    isAttackHit = false;

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
            angle = static_cast<float>(rand() % FULL_CIRCLE_DEGREES);  // ランダムな角度を取得
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

    //// HP減少時　Damageへ    HPが0以下の際には通らずDeathへ
    //if (hitPoint < currentHP && hitPoint > 0) {
    //    currentState = EnemyState::Damage;
    //}

    // アニメーションタイマーリセット
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


// Move状態の管理
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
    pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), ENEMY_CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS, CHARA_HIT_PUSH_POWER);

    // 移動後の座標を設定
    moveHandle();

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
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);

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


// Chase状態の管理
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
    if (pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), ENEMY_CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS, CHARA_HIT_PUSH_POWER))
        isColHit = true;

    // 移動後の座標を設定
    moveHandle();

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


// Attack状態の管理
void Enemy::attack()
{
    // 行動：攻撃

    // 当たり判定(手)設定 
    // アニメーションがアタッチされている必要があるのでここで処理
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
    // モデルの右手frame取得
    MATRIX frame_matrix = MV1GetFrameLocalWorldMatrix(animHandle, ENEMY_LEFT_HAND_FRAME);
    // 親の行列に合わせる
    mOBBColHand.setParentMatrix(frame_matrix);

    // 手OBB描画
    if (CheckHitKey(KEY_INPUT_E))
        mOBBColHand.draw(WHITE);

    // 手OBB,プレイヤーOBBでの当たり判定
    if (pGame->GetCollision()->checkOBBCol(mOBBColHand, pGame->GetPlayer()->GetOBBCol()))
    {
        isAttackHit = true;
    }

    // 遷移
    /*
        待機：
            条件：アニメーションの終了
    */
    // アニメーションタイマーリセット
    if (updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT))
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);

}


// Damage状態の管理
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


// Death状態の管理
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


// エネミーの視野メソッド
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


// 生き死にを結果として返す
bool Enemy::isAlive()
{
    // hitPointが0以下
    if (hitPoint <= 0 && isDeath)
        return false;

    return true;
}


// 描画メソッド
void Enemy::draw()
{
    // モデルにタイマーセット
    // これがないとアニメーションしない
    MV1SetAttachAnimTime(animHandle, 0, animTimer);

    // 画面に映る位置に3Dモデルを移動
    MV1SetPosition(animHandle, position);

    // モデルの大きさ変更
    MV1SetScale(animHandle, VGet(ENEMY_MODEL_SCALE, ENEMY_MODEL_SCALE, ENEMY_MODEL_SCALE));

    // モデルの回転
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // ３Ｄモデルの描画
    MV1DrawModel(animHandle);

    // 当たり判定カプセル描画
    if (CheckHitKey(KEY_INPUT_Q))
        DrawCapsule3D(position, VGet(position.x, position.y + ENEMY_CAP_HEIGHT, position.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
   
    // OBB描画
    if (CheckHitKey(KEY_INPUT_E))
    {
        // 当たっているときは赤色に
        if (pGame->GetPlayer()->GetIsHitFlag())
            mOBBCol.draw(RED);
        else
            mOBBCol.draw(WHITE);
    }
}


// mOBBColを取得して返す
OBBCollider Enemy::GetOBBCol()
{
    return mOBBCol;
}