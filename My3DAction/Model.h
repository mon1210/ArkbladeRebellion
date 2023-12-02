/*
* @file		Model.h
* @brief	クラス Model の宣言
* @note		
* 
*/
#pragma once


class Model
{
public:
	Model();
	~Model();
	virtual void LoadPlayerModel();	// Playerモデル読み込みメソッド
	virtual void LoadEnemyModel();	// Enemyモデル読み込みメソッド
	virtual void LoadTileModel();	// Tileモデル読み込みメソッド
	virtual int GetPlayerModel();	// Playerモデル取得メソッド
	virtual int GetEnemyModel();	// Enemyモデル取得メソッド
	virtual int GetTileModel();		// Tileモデル取得メソッド
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};