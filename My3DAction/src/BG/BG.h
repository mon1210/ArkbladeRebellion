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
	BG(Game *Game_);
	~BG();
	void draw();							// 描画メソッド
	// 以下取得用定数===================================================================== //
	int  GetModelHandle();					// モデル取得関数
	// 以上取得用定数===================================================================== //
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// 座標
	int		tileHandle = 0;					// 床モデル保存用
};
