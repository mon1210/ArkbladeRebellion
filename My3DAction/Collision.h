/**
* @file		Collider.h
* @brief	�N���X Collider �̐錾
* @note		�v���C���[�E���ɑ΂��ĉe������̂�Stage�Ŋ֐��g�p
*/
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"

// �N���X�̑O���錾
class Enemy;

class Collision
{
public:
	Collision();
	~Collision();
	virtual void initCollision(int handle);	// �����蔻���t�^����@��x����Stage�ŌĂяo���@���̓^�C���̂�
	virtual void setTileModel(int model);	// �^�C�����f�����Z�b�g����@Stage�ŌĂяo��

	// �ȉ�3������
	virtual void chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// �L�������m�̓����蔻��
	virtual void clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
protected:
	int tileHandle;

};