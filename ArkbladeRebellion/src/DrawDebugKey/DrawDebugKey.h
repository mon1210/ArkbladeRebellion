/**
* @file		DrawDebugKey.h
* @brief	クラス DrawDebugKey の宣言
* @note		デバッグ用のキーを明示する
*/
#pragma once
#include "..\Constants.h"
#include "DxLib.h"


class DrawDebugKey
{
public:
	/**
	* @brief DrawDebugKeyのコンストラクタ
	*/
	DrawDebugKey();

	/**
	* @brief DrawDebugKeyのデストラクタ
	*/
	~DrawDebugKey();

	/**
	* @brief 描画メソッド
	*/
	void draw();
};