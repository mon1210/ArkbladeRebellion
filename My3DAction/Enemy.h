/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "CharaBase.h"

#include "BG.h"
#include "Player.h"
#include "Animation.h"
#include "Constants.h"
#include "Enums.h"
#include "Game.h"
#include "Radar.h"

// クラスの前方宣言
class CharaBase;
class Game;
class Radar;

class Enemy : public CharaBase
{
public:
	Enemy(Game *parent);
	~Enemy();
	void initAnimation();	// アニメーション状態初期化関数 Stageで初期化時一度だけ呼び出す
	bool move() override;	// エネミーのアニメーションメソッド　true:生存 / false:死亡
	void draw() override;	// 描画メソッド
	void update() override;	// 状態管理とdraw呼び出し　毎フレーム呼び出される
	bool isTargetVisible();	// エネミーの視野　true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる 
	void animationHandle(eEnemy::AnimationNum num);	// アニメーションを設定する
	void setEnemyModel(int model);			// エネミーのモデルをセットする
	void setTileModel(int model);			// 床モデルをセットする　 床 => 当たり判定で使用
	void setPlayerPos(VECTOR player_pos);	// プレイヤーの座標をセットする
	VECTOR getEnemyPos();	// 座標取得メソッド
private:
	// 状態ごとのメソッド
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	Radar	*pRadar;
	VECTOR  playerPos;		// enemyToPlayerを求めるのに使用
	VECTOR  enemyToPlayer;	// エネミーからプレイヤーまでの距離
	int		tileHandle;
	int		count;			// フレーム計測用　行動遷移, で使用 
	float	hitPoint;
	float   vecLength;		// ベクトルの長さ保存用

	EnemyState currentState;
};