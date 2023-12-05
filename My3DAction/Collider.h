/**
* @file		Collider.h
* @brief	�����蔻��Ɋւ��邱�Ƃ��߂��w�b�_�t�@�C��
* @note		
*/
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"

// �N���X�̑O���錾
class Enemy;

class Collider
{
public:
	Collider();
	~Collider();
	virtual void InitCollision(int handle);	// �����蔻���t�^����@��x����Stage�ŌĂяo���@���̓^�C���̂�
	virtual void setTileModel(int model);	// �^�C�����f�����Z�b�g����@Stage�ŌĂяo��

	// �ȉ�3������
	virtual void Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// �L�������m�̓����蔻��
	virtual void ClampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
protected:
	int tileHandle;

};

#define CHARA_HIT_HEIGHT		250.f	// �����蔻��J�v�Z���̑傫��
#define CHARA_HIT_WIDTH			50.f	// �����蔻��J�v�Z���̔��a
#define CHARA_HIT_PUSH_POWER	20.f	// 