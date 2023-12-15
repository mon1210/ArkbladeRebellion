/*
* @file		BG.h
* @brief	クラス BG の宣言
* @note		床はここで管理
*/
#pragma once
#include "DxLib.h"
#include "stdafx.h"
#include "Game.h"

class Game;

class BG
{
public:
	BG(Game *Game_);
	~BG();
	void draw();							// 描画メソッド
	int  getModelHandle();					// モデル取得関数
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// 座標
	int		tileHandle = 0;					// モデル保存用変数
};
