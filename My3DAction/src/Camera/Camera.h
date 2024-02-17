/**
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
	/**
	* @brief Cameraのコンストラクタ
	*/
	Camera(Game *Game);

	/**
	* @brief Cameraのデストラクタ
	*/
	~Camera();

	/**
	* @brief カメラの更新
	*/
	void update();

	/**
	* @brief   プレイヤーの位置算出メソッド
	* @note    カメラの角度に合わせるのでCameraクラスで定義
	* @return  NewPlayerPos
	*/
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);

	// 以下取得用定数===================================================================== //
	/**
	* @brief カメラ水平角度を取得して返す
	*/
	float GetHorizontalAngle();
	// 以上取得用定数===================================================================== //
private:
	/**
	* @brief カメラ操作メソッド
	*/
	void control();

	/**
	* @brief 位置算出メソッド
	*/
	void setPosition(VECTOR player_pos);
private:
	Game	*pGame = nullptr;
	//! 座標
	VECTOR	position = VGet(0.f, 0.f, 0.f);
	//! 水平方向の角度
	float	hAngle = 0.f;
	//! 垂直方向の角度
	float	vAngle = 40.f;
};

