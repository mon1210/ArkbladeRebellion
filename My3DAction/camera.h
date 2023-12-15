/*
* @file		Camera.h
* @brief	�N���X Camera �̐錾
* @note		�v���C���[��Ǐ]����
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"
#include "Game.h"
#include <math.h>

class Game;

class Camera
{
public:
	Camera(Game *Game_);
	~Camera();
	void controller();											// �J�������상�\�b�h
	void update();												// �X�V���\�b�h
	void positionAndDirection(VECTOR player_pos);				// �J�����̈ʒu�Z�o���\�b�h
	float getHorizontalAngle();									// �J���������p�x�擾�֐�
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);	// �v���C���[�̈ʒu�Z�o���\�b�h(return playerPos)
protected:
	Game	*pGame = NULL;
	VECTOR	position = VGet(0.f, 0.f, 0.f);		// ���W
	float	hAngle = 0.f;						// ���������̊p�x
	float	vAngle = 40.f;						// ���������̊p�x
	float	sinParam = 0.f;
	float	cosParam = 0.f;
};

