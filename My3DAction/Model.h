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
	virtual void PlayerLoadModel();
	virtual void EnemyLoadModel();
	int		enemyHandle;
	int		playerHandle;
protected:
};