/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "CharaBase.h"

#include <math.h>
#include "BG.h"
#include "Player.h"
#include "Animation.h"
#include "Constants.h"
#include "Enums.h"
#include "Game.h"

// クラスの前方宣言
class CharaBase;
class Game;

class Enemy : public CharaBase
{
public:
	Enemy(Game *Game_);
	~Enemy();
	void initAnimation();							// アニメーション状態初期化関数 Stageで初期化時一度だけ呼び出す
	bool move() override;							// エネミーのアニメーションメソッド　true:生存 / false:死亡
	void draw() override;							// 描画メソッド
	void update() override;							// 状態管理とdraw呼び出し　毎フレーム呼び出される
	VECTOR getPos() override;						// 座標取得メソッド
	bool isTargetVisible();							// エネミーの視野　true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる 
	void animationHandle(eEnemy::AnimationNum num);	// アニメーションを設定する
	void updateEnemyToPlayerVec();					// enemyToPlayerの更新・長さを算出　毎フレーム呼び出す}
private:
	// 状態ごとのメソッド
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	Game	*pGame = NULL;
	VECTOR  enemyToPlayer = VGet(0.f, 0.f, 0.f);	// エネミーからプレイヤーまでの距離
	int		tileHandle = 0;							// 床モデルハンドル
	int		count = 0;								// フレーム計測用　行動遷移, で使用 
	float   vecLength = 0.f;						// ベクトルの長さ保存用

	EnemyState currentState = EnemyState::Wait;
};