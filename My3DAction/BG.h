#pragma once
#include "DxLib.h"
#include "IGameObject.h"

class BG
{
public:
	BG();
	virtual ~BG();
	virtual void draw();	// 描画メソッド
	virtual int GetModelHandle();	// モデル取得関数
	virtual void setTileModel(int model);
protected:
	VECTOR	position;		// 座標
	int		tile_handle;	// モデル保存用変数
};
