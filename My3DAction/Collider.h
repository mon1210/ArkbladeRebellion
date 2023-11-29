
#pragma once
#include "DxLib.h"

class Player;
class Enemy;

class Collider
{
public:
	Collider();
	~Collider();
	virtual void Chara_Collision(Player* player, Enemy* enemy);
	virtual void draw();
private:

};

#define CHARA_HIT_HEIGHT		250.f	// 当たり判定カプセルの大きさ
#define CHARA_HIT_WIDTH			50.f	// 当たり判定カプセルの半径
#define CHARA_HIT_PUSH_POWER	20.f	// 