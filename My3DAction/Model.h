/*
* @file		Model.h
* @brief	�N���X Model �̐錾
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