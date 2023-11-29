
#pragma once
#include "DxLib.h"

class Enemy;

class Collider
{
public:
	Collider();
	~Collider();
	virtual void Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* moveVec);
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int difColor, int spcColor, int flag);
private:

};

#define CHARA_HIT_HEIGHT		250.f	// 当たり判定カプセルの大きさ
#define CHARA_HIT_WIDTH			50.f	// 当たり判定カプセルの半径
#define CHARA_HIT_PUSH_POWER	20.f	// 