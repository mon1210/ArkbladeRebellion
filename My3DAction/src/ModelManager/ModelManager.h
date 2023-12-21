/*
* @file		ModelManager.h
* @brief	�N���X ModelManager �̐錾
* @note		���f���Ɋւ��鏈�����Ǘ�����
* 
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include <unordered_map>


class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	void initializeModelList();			// unordered_map���������\�b�h�@�߂�l�ɂȂ�ϐ���o�^	
	// �ȉ��擾�p�萔===================================================================== //
	int GetHandle(ModelType type_);		// ���f�����擾���ĕԂ����\�b�h
	// �ȏ�擾�p�萔===================================================================== //
protected:
	int		playerHandle = 0;						// �v���C���[���f���ۑ��p
	int		enemyHandle = 0;						// �G�l�~�[���f���ۑ��p
	int		tileHandle = 0;							// �����f���ۑ��p

	std::unordered_map<ModelType, int> modelList;	// ���f���n���h���̓�����unordered_map���`
};