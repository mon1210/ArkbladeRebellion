/*
* @file		Model.h
* @brief	�N���X Model �̐錾
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
	void loadModel();		// ���f���ǂݍ��݃��\�b�h�@Stage�ŌĂяo��
	int getPlayerModel();	// Player���f�����擾���ĕԂ����\�b�h
	int getEnemyModel();	// Enemy���f�����擾���ĕԂ����\�b�h
	int getTileModel();		// Tile���f�����擾���ĕԂ����\�b�h
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};