/*
* @file		Camera.h
* @brief	�N���X Camera �̐錾
* @note		�v���C���[��Ǐ]���邽�߁A�قƂ�ǂ̃��\�b�h��Player�N���X�ŌĂяo��
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
	virtual void CameraController();
	virtual VECTOR MoveAlongHAngle(VECTOR moveVec,VECTOR pPlayerPos);
	virtual void SetCameraPositionAndDirection(VECTOR pPlayerPos);
	float  CameraHAngle;	// ���������̊p�x
	float  CameraVAngle;	// ���������̊p�x
private:
	float  SinParam;
	float  CosParam;
	VECTOR	cameraPos;
	VECTOR	playerPos;
};

