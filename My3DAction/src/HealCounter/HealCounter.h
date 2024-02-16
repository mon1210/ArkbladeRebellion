/**
* @file		HealCounter.h
* @brief	クラス HealCounter の宣言
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"

// クラスの前方宣言
class Game;

class HealCounter
{
public:
	/**
	* @brief HealCounterのコンストラクタ
	*/
	HealCounter(Game *Game_);
	~HealCounter();
	/**
	* @brief 描画メソッド
	*/
	void draw();
	/**
	* @brief 更新メソッド
	* @note  残り回数に合わせて色変更
	*/
	void update();
private:
	Game *pGame = nullptr;
	unsigned int color = 0;		// UIの色
};

