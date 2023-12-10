/*
* @file		Model.h
* @brief	クラス Model の宣言
* @note		
* 
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"


class Model
{
public:
	Model();
	~Model();
	void loadModel();		// モデル読み込みメソッド　Stageで呼び出す
	int getPlayerModel();	// Playerモデルを取得して返すメソッド
	int getEnemyModel();	// Enemyモデルを取得して返すメソッド
	int getTileModel();		// Tileモデルを取得して返すメソッド
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};