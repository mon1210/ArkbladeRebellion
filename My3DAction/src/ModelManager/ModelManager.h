/*
* @file		ModelManager.h
* @brief	�N���X ModelManager �̐錾
* @note		���f���Ɋւ��鏈�����Ǘ�����
* 
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"


class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	// �ȉ��擾�p�萔===================================================================== //
	int GetPlayerModel();		// Player���f�����擾���ĕԂ����\�b�h
	int GetEnemyModel();		// Enemy���f�����擾���ĕԂ����\�b�h
	int GetTileModel();			// Tile���f�����擾���ĕԂ����\�b�h
	// �ȏ�擾�p�萔===================================================================== //
protected:
	int		playerHandle = 0;	// �v���C���[���f���ۑ��p
	int		enemyHandle = 0;	// �G�l�~�[���f���ۑ��p
	int		tileHandle = 0;		// �����f���ۑ��p
};