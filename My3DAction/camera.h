/*
* @file		Camera.h
* @brief	クラス Camera の宣言
* @note		プレイヤーを追従するため、ほとんどのメソッドをPlayerクラスで呼び出す
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
	float  CameraHAngle;	// 水平方向の角度
	float  CameraVAngle;	// 垂直方向の角度
private:
	float  SinParam;
	float  CosParam;
	VECTOR	cameraPos;
	VECTOR	playerPos;
};

