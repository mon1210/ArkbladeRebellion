/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"

//--- ヘッダガードを使用して二度インクルードするのを防ぐ
#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class Stage;
class Model;

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	virtual bool move() override;	// エネミーのアニメーションメソッド　true:生存 / false:死亡
	virtual void draw() override;	// 描画メソッド
	virtual void SetMove();		// 行動管理関数
	virtual void SetAnim(eEnemy::AnimationNum num);		// アニメーションセット関数
	virtual VECTOR GetEnemyPos();	// 座標取得関数
protected:
	Model*	pModel;
	VECTOR	position;
	int		animHandle;
	int		animNo;
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;

private:

};