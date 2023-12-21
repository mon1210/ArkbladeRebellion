#include "ModelManager.h"


/**
* @brief Model�̃R���X�g���N�^
*
*/
ModelManager::ModelManager()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");

    // unordered_map������
    initializeModelList();
}


// �f�X�g���N�^
ModelManager::~ModelManager()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief unordered_map���������\�b�h�@	
* @note  �߂�l�ɂȂ�ϐ���o�^
*/
void ModelManager::initializeModelList()
{
    modelList[ModelType::Player] = { playerHandle };
    modelList[ModelType::Enemy]  = { enemyHandle  };
    modelList[ModelType::Tile]   = { tileHandle   };

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
