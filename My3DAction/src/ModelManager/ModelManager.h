/*
* @file		ModelManager.h
* @brief	�N���X ModelManager �̐錾
* @note		���f���Ɋւ��鏈�����Ǘ�����
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include <unordered_map>


class ModelManager
{
public:
	/**
	* @brief Model�̃R���X�g���N�^
	*/
	ModelManager();
	~ModelManager();
	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief ���f�����擾���ĕԂ�
	*/
	int GetHandle(ModelType type);
	// �ȏ�擾�p�萔===================================================================== //
private:
	/**
	* @brief unordered_map���������\�b�h�@
	* @note  �o�^�Ɠ�����ZBuffer���K�p����
	*/
	void initializeModelList();
private:
	std::unordered_map<ModelType, int> modelList;	// ���f���n���h���̓�����unordered_map���`
};