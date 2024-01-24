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
	// �ȉ��擾�p�萔===================================================================== //
	int GetHandle(ModelType type_);					// ���f�����擾���ĕԂ����\�b�h
	// �ȏ�擾�p�萔===================================================================== //
private:
	void initializeModelList();						// unordered_map���������\�b�h�@�߂�l�ɂȂ�ϐ���o�^	
private:
	std::unordered_map<ModelType, int> modelList;	// ���f���n���h���̓�����unordered_map���`
};