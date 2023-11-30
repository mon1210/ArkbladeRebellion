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
	virtual void LoadPlayerModel();
	virtual void LoadEnemyModel();
	virtual void LoadTileModel();
	virtual int GetPlayerModel();
	virtual int GetEnemyModel();
	virtual int GetTileModel();
protected:
	int		enemyHandle;
	int		playerHandle;
	int		tileHandle;
};