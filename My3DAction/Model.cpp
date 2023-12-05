#include "Model.h"


/**
* @brief Model�̃R���X�g���N�^
*
*/
Model::Model()
{
    enemyHandle = 0;
    playerHandle = 0;
    tileHandle = 0;

}


// �f�X�g���N�^
Model::~Model()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief ���f���ǂݍ��݃��\�b�h
*/
void Model::LoadModel()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


/**
* @brief �v���C���[���f�����擾���ĕԂ�
*/
int Model::GetPlayerModel()
{
    return playerHandle;
}


/**
* @brief �G�l�~�[���f�����擾���ĕԂ�
*/
int Model::GetEnemyModel()
{
    return enemyHandle;
}


/**
* @brief �^�C�����f�����擾���ĕԂ�
*/
int Model::GetTileModel()
{
    return tileHandle;
}
