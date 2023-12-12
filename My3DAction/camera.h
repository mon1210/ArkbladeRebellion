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
	void controller();			// カメラ操作メソッド
	void setPositionAndDirection(VECTOR player_pos);			// カメラの位置算出メソッド
	float getHorizontalAngle();	// カメラ水平角度取得関数
	float getVerticalAngle();	// カメラ垂直角度取得関数
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);	// プレイヤーの位置算出メソッド(return playerPos)
protected:
	VECTOR	position;
	VECTOR	playerPos;
	float	hAngle;	// 水平方向の角度
	float	vAngle;	// 垂直方向の角度
	float	sinParam;
	float	cosParam;
};

