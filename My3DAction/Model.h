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
	virtual void LoadModel();	// モデル読み込みメソッド
	virtual int GetPlayerModel();	// Playerモデル取得メソッド
	virtual int GetEnemyModel();	// Enemyモデル取得メソッド
	virtual int GetTileModel();		// Tileモデル取得メソッド
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};