
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

#define CHARA_HIT_HEIGHT		250.f	// �����蔻��J�v�Z���̑傫��
#define CHARA_HIT_WIDTH			50.f	// �����蔻��J�v�Z���̔��a
#define CHARA_HIT_PUSH_POWER	20.f	// 