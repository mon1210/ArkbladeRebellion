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
	/*
	* @brief HPBarのコンストラクタ
	*/
	HPBar(Game *Game_);
	~HPBar();
	/*
	* @brief 描画メソッド
	* @note  体力低下でバーの色変更
	*/
	void draw();
	/*
	* @brief 変動処理
	* @note  滑らかなHPの増減を実装
	*/
	void update();
private:
	Game	*pGame = nullptr;
	float	currnetPlayerHp = 0.f;	// 現在のPlayerのHP
	float	currnetEnemyHp = 0.f;	// 現在のEnemyのHP

};
