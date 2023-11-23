/*
* @file	 model.h
* @brief
*
*
*/
#pragma once

class Player;

class Model
{
public:
	Model();
	~Model();
	virtual void ModelSet();
	int		enemyHandle;
	int		playerHandle;
protected:
	Player* pPlayer;
	//static int	enemyHandle;
	//static int	playerHandle;
};