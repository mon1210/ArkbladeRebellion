/*
* @file		BG.h
* @brief	クラス BG の宣言
* @note		床はここで管理
*/
#pragma once
#include "DxLib.h"
#include "stdafx.h"

class BG
{
public:
	BG();
	~BG();
	void draw();					// 描画メソッド
	void setTileModel(int model);	// タイルモデルをセットする
	int  getModelHandle();			// モデル取得関数
protected:
	VECTOR	position;		// 座標
	int		tile_handle;	// モデル保存用変数
};
