/*
* @file		ModelManager.h
* @brief	クラス ModelManager の宣言
* @note		モデルに関する処理を管理する
* 
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"


class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	void loadModel();		// モデル読み込みメソッド　Stageで呼び出す
	int getPlayerModel();	// Playerモデルを取得して返すメソッド
	int getEnemyModel();	// Enemyモデルを取得して返すメソッド
	int getTileModel();		// Tileモデルを取得して返すメソッド
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};