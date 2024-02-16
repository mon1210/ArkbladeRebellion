/*
* @file		BG.h
* @brief	クラス BG の宣言
* @note		床はここで管理
*/
#pragma once
#include "DxLib.h"
#include "..\stdafx.h"
#include "..\Game\Game.h"

class Game;

class BG
{
public:
	/**
	* @brief BGのコンストラクタ
	*/
	BG(Game *Game);

	// デストラクタ
	~BG();

	/**
	* @brief 描画メソッド
	* @note  画面上に見えている部分のみ描画
	*/
	void draw();

	// 以下取得用定数===================================================================== //
	/**
	* @brief 床モデルを取得して返す
	*/
	int  GetModelHandle();
	// 以上取得用定数===================================================================== //
private:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// 座標
	int		tileHandle = 0;					// 床モデル保存用
};
