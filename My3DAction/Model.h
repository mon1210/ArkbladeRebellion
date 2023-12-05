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
	virtual void LoadModel();		// モデル読み込みメソッド　Stageで呼び出す
	virtual int GetPlayerModel();	// Playerモデルを取得して返すメソッド
	virtual int GetEnemyModel();	// Enemyモデルを取得して返すメソッド
	virtual int GetTileModel();		// Tileモデルを取得して返すメソッド
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};