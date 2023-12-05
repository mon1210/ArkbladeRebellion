/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "IGameObject.h"

// クラスの前方宣言
class Stage;

class Enemy : public IGameObject
{
public:
	Enemy(Stage *parent);
	~Enemy();
	virtual void InitAnimation();
	virtual void Update();
	virtual bool IsTargetVisible();
	virtual bool move() override;	// エネミーのアニメーションメソッド　true:生存 / false:死亡
	virtual void draw() override;	// 描画メソッド
	virtual void SetMove();		// 行動管理関数
	virtual void SetAnim(eEnemy::AnimationNum num);		// アニメーションセット関数
	virtual VECTOR GetEnemyPos();	// 座標取得関数
	virtual void setEnemyModel(int model);
	virtual void setTileModel(int model);
	virtual void setPlayerPos(VECTOR player_pos);
private:
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	VECTOR	position;
	VECTOR  playerPos;
	VECTOR  enemyToPlayer;	// エネミーからプレイヤーまでの距離
	int		animHandle;
	int		tileHandle;
	int		animNo;
	int		count;		// フレーム計測用　行動遷移, で使用 
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;
	float   vecLength;	// ベクトルの長さ保存用

	EnemyState currentState;
private:


};