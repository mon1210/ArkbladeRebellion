/**
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
	* @brief ModelManager�̃R���X�g���N�^
	*/
	ModelManager();

	/**
	* @brief ModelManager�̃f�X�g���N�^
	*/
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
	//! ���f���n���h���̓�����unordered_map���`
	std::unordered_map<ModelType, int> modelList;
};