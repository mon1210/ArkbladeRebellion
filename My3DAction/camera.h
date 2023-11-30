/*
* @file		Camera.h
* @brief	�N���X Camera �̐錾
* @note		�v���C���[��Ǐ]���邽�߁A�قƂ�ǂ̃��\�b�h��Player�N���X�ŌĂяo��
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"
#include <math.h>

class Collider;
class Enemy;

class Camera
{
public:
	Camera();
	~Camera();
	virtual void CameraController();
	virtual VECTOR MoveAlongHAngle(VECTOR move_vec,VECTOR player_pos);
	virtual void SetCameraPositionAndDirection(VECTOR pPlayerPos);
	virtual float GetCameraHorizontalAngle();
	virtual float GetCameraVerticalAngle();
private:
	Collider*	pCollider;
	Enemy*		pEnemy;
	VECTOR	cameraPos;
	VECTOR	playerPos;
	float	CameraHAngle;	// ���������̊p�x
	float	CameraVAngle;	// ���������̊p�x
	float	SinParam;
	float	CosParam;
};

