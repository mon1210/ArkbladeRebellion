#include "ModelManager.h"


/**
* @brief Model�̃R���X�g���N�^
*
*/
ModelManager::ModelManager()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


// �f�X�g���N�^
ModelManager::~ModelManager()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief �v���C���[���f�����擾���ĕԂ�
*/
int ModelManager::GetPlayerModel()
{
    return playerHandle;
}


/**
* @brief �G�l�~�[���f�����擾���ĕԂ�
*/
int ModelManager::GetEnemyModel()
{
    return enemyHandle;
}


/**
* @brief �^�C�����f�����擾���ĕԂ�
*/
int ModelManager::GetTileModel()
{
    return tileHandle;
}
