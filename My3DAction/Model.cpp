
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

}


// �f�X�g���N�^
Model::~Model()
{
}


/**
* @brief �v���C���[���f���ǂݍ��݊֐�
*/
void Model::PlayerLoadModel()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
}


/**
* @brief  �G�l�~�[���f���ǂݍ��݊֐�
*/
void Model::EnemyLoadModel()
{
    // 3D���f���̓ǂݍ���
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
}
