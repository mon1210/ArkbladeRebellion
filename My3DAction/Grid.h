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
	virtual void Draw();	// 描画メソッド
protected:
	VECTOR startHorizontal;		// 水平方向の開始地点
	VECTOR endHorizontal;		// 水平方向の最終地点 
	VECTOR startVertical;		// 垂直方向の開始地点
	VECTOR endVertical;			// 垂直方向の最終地点
};
