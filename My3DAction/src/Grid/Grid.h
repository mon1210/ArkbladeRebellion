/*
* @file		Grid.h
* @brief	クラス Grid の宣言
* @note		3Dモデルの位置を視覚的にわかりやすくするために、地面にラインを表示する
*/
#pragma once
#include "..\Constants.h"
#include "DxLib.h"


class Grid
{
public:
	/**
	* @brief Gridのコンストラクタ
	*/
	Grid();
	~Grid();
	/**
	* @brief 描画関数
	* @note  Game::draw()で呼び出し
	*/
	void draw();
private:
	VECTOR startHorizontal = VGet(0.f, 0.f, 0.f);	// 水平方向の開始地点
	VECTOR endHorizontal = VGet(0.f, 0.f, 0.f);		// 水平方向の最終地点 
	VECTOR startVertical = VGet(0.f, 0.f, 0.f);		// 垂直方向の開始地点
	VECTOR endVertical = VGet(0.f, 0.f, 0.f);		// 垂直方向の最終地点
};
