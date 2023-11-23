/*
* @file	 model.h
* @brief
*
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