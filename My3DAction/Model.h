/*
* @file		Model.h
* @brief	ƒNƒ‰ƒX Model ‚ÌéŒ¾
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