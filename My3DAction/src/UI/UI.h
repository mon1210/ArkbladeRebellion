/**
* @file		UI.h
* @brief	クラス UI の宣言
*/
#pragma once
#include "..\Constants.h"
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
	Game	*pGame = NULL;
	float	hpRatio = 0.f;	// HPバーの表示比率

};

#define GREEN GetColor(0, 255, 0) 
#define WHITE GetColor(255, 255, 255)