#include "ModelManager.h"


/**
* @brief Model�̃R���X�g���N�^
*
*/
ModelManager::ModelManager()
{
    // unordered_map������
    initializeModelList();
}


// �f�X�g���N�^
ModelManager::~ModelManager()
{
}


/**
* @brief unordered_map���������\�b�h�@	
* @note  �߂�l�ɂȂ�ϐ���o�^
*/
void ModelManager::initializeModelList()
{
    modelList[ModelType::Player] = { MV1LoadModel("res\\Player\\PlayerModel.mv1") };
    modelList[ModelType::Enemy]  = { MV1LoadModel("res\\Enemy\\EnemyModel2.mv1") };
    modelList[ModelType::Tile]   = { MV1LoadModel("res\\test_Tile_model.mv1") };
}


/**
* @brief ���f�����擾���ĕԂ�
*/
int ModelManager::GetHandle(ModelType type_)
{
    // ���X�g����łȂ��Ƃ�
    if (modelList.count(type_) > 0)
    {
        return modelList[type_];
    }

    return modelList[ModelType::No];
}
