/*
*
*
*
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
	virtual void FollowCamera(VECTOR pos);
	virtual void CameraController();
	virtual VECTOR MoveAlongHAngle(bool moveflag,VECTOR moveVec,VECTOR pPlayerPos);
	virtual void SetCameraPositionAndDirection(VECTOR pPlayerPos);
	float  CameraHAngle;	// 水平方向の角度
	float  CameraVAngle;	// 垂直方向の角度
private:
	float  SinParam;
	float  CosParam;
	VECTOR	cameraPos;
	VECTOR	playerPos;
};

