/*
* @file		Grid.h
* @brief	クラス Grid の宣言
* @note		3Dモデルの位置を視覚的にわかりやすくするために、地面にラインを表示する
*/
#pragma once
#include "Constants.h"
#include "DxLib.h"


class Grid
{
public:
	Grid();
	~Grid();
	virtual void Draw();
protected:
	VECTOR startHorizontal;
	VECTOR endHorizontal;
	VECTOR startVertical;
	VECTOR endVertical;
};
