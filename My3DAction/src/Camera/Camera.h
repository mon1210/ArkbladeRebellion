/*
* @file		Camera.h
* @brief	クラス Camera の宣言
* @note		プレイヤーを追従する
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"
#include <math.h>

class Game;

class Camera
{
public:
	Camera(Game *Game_);
	~Camera();
	void update();												// 更新メソッド	
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);	// プレイヤーの位置算出メソッド(return playerPos)
	// 以下取得用定数===================================================================== //
	float GetHorizontalAngle();									// カメラ水平角度取得関数	
	// 以上取得用定数===================================================================== //
private:
	void control();												// カメラ操作メソッド
	void setPosition(VECTOR player_pos);						// カメラの位置算出メソッド
private:
	Game	*pGame = nullptr;
	VECTOR	position = VGet(0.f, 0.f, 0.f);		// 座標
	float	hAngle = 0.f;						// 水平方向の角度
	float	vAngle = 40.f;						// 垂直方向の角度
};

