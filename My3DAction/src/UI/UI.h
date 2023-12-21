/**
* @file		UI.h
* @brief	クラス UI の宣言
*/
#pragma once
#include "..\Constants.h"
#include "..\Colors.h"
#include "..\Game\Game.h"

class Game;

class UI
{
public:
	UI(Game *Game_);
	~UI();
	void move();			// UIの変動用メソッド
	void draw();			// 描画用メソッド
private:
protected:
	Game	*pGame = nullptr;
	float	hpRatio = 0.f;	// HPバーの表示比率

};
