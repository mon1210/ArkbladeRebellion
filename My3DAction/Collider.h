
#pragma once
#include "DxLib.h"

class Enemy;
class BG;

class Collider
{
public:
	Collider();
	~Collider();
	virtual void Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);
	virtual void ClampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
private:
	BG* pBG;
};

#define CHARA_HIT_HEIGHT		250.f	// 当たり判定カプセルの大きさ
#define CHARA_HIT_WIDTH			50.f	// 当たり判定カプセルの半径
#define CHARA_HIT_PUSH_POWER	20.f	// 