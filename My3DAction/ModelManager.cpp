#include "ModelManager.h"


/**
* @brief Model�̃R���X�g���N�^
*
*/
ModelManager::ModelManager()
{
    loadModel();
}


// �f�X�g���N�^
ModelManager::~ModelManager()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief ���f���ǂݍ��݃��\�b�h
*/
void ModelManager::loadModel()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


/**
* @brief �v���C���[���f�����擾���ĕԂ�
*/
int ModelManager::getPlayerModel()
{
    return playerHandle;
}


/**
* @brief �G�l�~�[���f�����擾���ĕԂ�
*/
int ModelManager::getEnemyModel()
{
    return enemyHandle;
}


/**
* @brief �^�C�����f�����擾���ĕԂ�
*/
int ModelManager::getTileModel()
{
    return tileHandle;
}
