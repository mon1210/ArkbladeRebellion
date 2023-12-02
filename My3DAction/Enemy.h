/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "IGameObject.h"

class Model;
class BG;

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	virtual void InitAnimation();
	virtual void Update();
	virtual bool IsTargetVisible();
	virtual bool move() override;	// エネミーのアニメーションメソッド　true:生存 / false:死亡
	virtual void draw() override;	// 描画メソッド
	virtual void SetMove();		// 行動管理関数
	virtual void SetAnim(eEnemy::AnimationNum num);		// アニメーションセット関数
	virtual VECTOR GetEnemyPos();	// 座標取得関数
private:
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	Model*	pModel;
	BG*		pBG;
	VECTOR	position;
	int		animHandle;
	int		animNo;
	int		count;		// フレーム計測用　行動遷移, で使用 
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;

	EnemyState currentState;
private:


};