/*
* @file		Camera.h
* @brief	クラス Camera の宣言
* @note		プレイヤーを追従するため、ほとんどのメソッドをPlayerクラスで呼び出す
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
	float	CameraHAngle;	// 水平方向の角度
	float	CameraVAngle;	// 垂直方向の角度
	float	SinParam;
	float	CosParam;
};

