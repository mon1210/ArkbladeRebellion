/**
* @file		Collision.h
* @brief	�N���X Collision �̐錾
* @note		�v���C���[�E���ɑ΂��ĉe������̂�Game�Ŋ֐��g�p
*/
#pragma once
#include "DxLib.h"
#include "..\Game\Game.h"

// �N���X�̑O���錾
class Game;

class Collision
{
public:
	Collision(Game *Game_);
	~Collision();
	void initCollision(int handle);																// �����蔻���t�^����@��x����Stage�ŌĂяo���@���̓^�C���̂�
	bool clampToStageBounds(VECTOR& new_pos, VECTOR& pos);								// �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
	void charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR& pos2, 
		float cap1_height, float cap2_height, float cap1_radius, float cap2_radius);	// �L�������m�̃J�v�Z�������蔻�胁�\�b�h
protected:
	Game *pGame = nullptr;
	int tileHandle = 0;		// �����f���ۑ��p

};