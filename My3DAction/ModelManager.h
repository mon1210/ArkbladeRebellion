/*
* @file		ModelManager.h
* @brief	�N���X ModelManager �̐錾
* @note		���f���Ɋւ��鏈�����Ǘ�����
* 
*/
#pragma once
#include "DxLib.h"
#include "Constants.h"


class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	void loadModel();		// ���f���ǂݍ��݃��\�b�h�@Stage�ŌĂяo��
	int getPlayerModel();	// Player���f�����擾���ĕԂ����\�b�h
	int getEnemyModel();	// Enemy���f�����擾���ĕԂ����\�b�h
	int getTileModel();		// Tile���f�����擾���ĕԂ����\�b�h
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};