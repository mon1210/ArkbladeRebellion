/**
* @file		HPBar.h
* @brief	クラス HPBar の宣言
*/
#pragma once
#include "..\Constants.h"
#include "..\Game\Game.h"

class Game;

class HPBar
{
public:
	HPBar(Game *Game_);
	~HPBar();
	void update();			// UIの変動用メソッド
	void draw();			// 描画用メソッド
private:
protected:
	Game	*pGame = nullptr;
	float	hpRatio = 0.f;	// HPバーの表示比率

};
