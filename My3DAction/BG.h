#pragma once
#include "DxLib.h"

#ifndef __IGAMEOBJECT_H__
//ゲーム上のオブジェクトを表現するクラスを汎化したインターフェースの宣言
#include "IGameObject.h"
#endif

class Model;

class BG
{
public:
	BG();
	virtual ~BG();
	virtual void draw();
	virtual int GetModelHandle();
protected:
	Model*	pModel;
	int		tile_handle;
	VECTOR	position;
};
