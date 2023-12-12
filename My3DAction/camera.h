/*
* @file		Camera.h
* @brief	�N���X Camera �̐錾
* @note		�v���C���[��Ǐ]����
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"
#include <math.h>


class Camera
{
public:
	Camera();
	~Camera();
	void controller();			// �J�������상�\�b�h
	void setPositionAndDirection(VECTOR player_pos);			// �J�����̈ʒu�Z�o���\�b�h
	float getHorizontalAngle();	// �J���������p�x�擾�֐�
	float getVerticalAngle();	// �J���������p�x�擾�֐�
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);	// �v���C���[�̈ʒu�Z�o���\�b�h(return playerPos)
protected:
	VECTOR	position;
	VECTOR	playerPos;
	float	hAngle;	// ���������̊p�x
	float	vAngle;	// ���������̊p�x
	float	sinParam;
	float	cosParam;
};

