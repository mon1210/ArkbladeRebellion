/*
* @file		Camera.h
* @brief	�N���X Camera �̐錾
* @note		�v���C���[��Ǐ]����
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"
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
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);	// �v���C���[�̈ʒu�Z�o���\�b�h(return playerPos)
	// �ȉ��擾�p�萔===================================================================== //
	float GetHorizontalAngle();									// �J���������p�x�擾�֐�	
	// �ȏ�擾�p�萔===================================================================== //
protected:
	Game	*pGame = nullptr;
	VECTOR	position = VGet(0.f, 0.f, 0.f);		// ���W
	float	hAngle = 0.f;						// ���������̊p�x
	float	vAngle = 40.f;						// ���������̊p�x
};

