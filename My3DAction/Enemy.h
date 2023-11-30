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
	virtual bool move() override;
	virtual void draw() override;
	virtual void SetMove();
	virtual void SetAnim(eEnemy::AnimationNum num);
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