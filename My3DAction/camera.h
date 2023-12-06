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
	virtual void CameraController();	// �J�������상�\�b�h
	virtual VECTOR MoveAlongHAngle(VECTOR move_vec,VECTOR player_pos);	// �v���C���[�̈ʒu�Z�o���\�b�h(return playerPos)
	virtual void SetCameraPositionAndDirection(VECTOR player_pos);		// �J�����̈ʒu�Z�o���\�b�h
	virtual float GetCameraHorizontalAngle();	// �J���������p�x�擾�֐�
	virtual float GetCameraVerticalAngle();		// �J���������p�x�擾�֐�
protected:
	VECTOR	cameraPos;
	VECTOR	playerPos;
	float	CameraHAngle;	// ���������̊p�x
	float	CameraVAngle;	// ���������̊p�x
	float	SinParam;
	float	CosParam;
};

