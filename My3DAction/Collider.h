
#pragma once
#include "DxLib.h"

class Enemy;
class BG;

class Collider
{
public:
	Collider();
	~Collider();
	virtual void Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// �L�������m�̓����蔻��
	virtual void ClampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
private:
	BG* pBG;
};

#define CHARA_HIT_HEIGHT		250.f	// �����蔻��J�v�Z���̑傫��
#define CHARA_HIT_WIDTH			50.f	// �����蔻��J�v�Z���̔��a
#define CHARA_HIT_PUSH_POWER	20.f	// 