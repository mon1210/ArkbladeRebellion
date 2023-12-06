/*
* @file		Camera.h
* @brief	クラス Camera の宣言
* @note		プレイヤーを追従する
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
	virtual void CameraController();	// カメラ操作メソッド
	virtual VECTOR MoveAlongHAngle(VECTOR move_vec,VECTOR player_pos);	// プレイヤーの位置算出メソッド(return playerPos)
	virtual void SetCameraPositionAndDirection(VECTOR player_pos);		// カメラの位置算出メソッド
	virtual float GetCameraHorizontalAngle();	// カメラ水平角度取得関数
	virtual float GetCameraVerticalAngle();		// カメラ垂直角度取得関数
protected:
	VECTOR	cameraPos;
	VECTOR	playerPos;
	float	CameraHAngle;	// 水平方向の角度
	float	CameraVAngle;	// 垂直方向の角度
	float	SinParam;
	float	CosParam;
};

