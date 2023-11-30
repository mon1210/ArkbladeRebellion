
#include "DxLib.h"
#include "Constants.h"
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
}


/**
* @brief �v���C���[���f���ǂݍ��݊֐�
*/
void Model::LoadPlayerModel()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
}


/**
* @brief �G�l�~�[���f���ǂݍ��݊֐�
*/
void Model::LoadEnemyModel()
{
    // 3D���f���̓ǂݍ���
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
}


/**
* @brief �^�C�����f���ǂݍ��݊֐�
*/
void Model::LoadTileModel()
{
    // 3D���f���̓ǂݍ���
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
 }


/**
* @brief �v���C���[���f���擾�p�֐�
*/
int Model::GetPlayerModel()
{
    return playerHandle;
}


/**
* @brief �G�l�~�[���f���擾�p�֐�
*/
int Model::GetEnemyModel()
{
    return enemyHandle;
}


/**
* @brief �^�C�����f���擾�p�֐�
*/
int Model::GetTileModel()
{
    return tileHandle;
}
