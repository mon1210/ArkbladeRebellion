/*
* @file		Camera.h
* @brief	クラス Camera の宣言
* @note		プレイヤーを追従する
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"
#include "Game.h"
#include <math.h>

class Game;

class Camera
{
public:
	Camera(Game *Game_);
	~Camera();
	void controller();											// カメラ操作メソッド
	void update();												// 更新メソッド
	void positionAndDirection(VECTOR player_pos);				// カメラの位置算出メソッド
	float getHorizontalAngle();									// カメラ水平角度取得関数
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);	// プレイヤーの位置算出メソッド(return playerPos)
protected:
	Game	*pGame = NULL;
	VECTOR	position = VGet(0.f, 0.f, 0.f);		// 座標
	float	hAngle = 0.f;						// 水平方向の角度
	float	vAngle = 40.f;						// 垂直方向の角度
	float	sinParam = 0.f;
	float	cosParam = 0.f;
};

