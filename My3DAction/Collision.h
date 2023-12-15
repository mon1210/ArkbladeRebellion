/**
* @file		Collision.h
* @brief	�N���X Collision �̐錾
* @note		�v���C���[�E���ɑ΂��ĉe������̂�Game�Ŋ֐��g�p
*/
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"

// �N���X�̑O���錾
class Enemy;
class Game;

class Collision
{
public:
	Collision(Game *Game_);
	~Collision();
	virtual void initCollision(int handle);	// �����蔻���t�^����@��x����Stage�ŌĂяo���@���̓^�C���̂�

	// �ȉ�3������
	virtual void chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// �L�������m�̓����蔻��
	virtual void clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
protected:
	int tileHandle;

};