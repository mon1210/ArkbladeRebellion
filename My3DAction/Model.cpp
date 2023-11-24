/*
* @file	 Model.h
* @brief
*
*
*/
#include "DxLib.h"
#include "Constants.h"
#include "Model.h"


// 
Model::Model()
{
    enemyHandle = 0;
    playerHandle = 0;

}


// 
Model::~Model()
{
}


// 
void Model::PlayerLoadModel()
{
    // 3D���f���̓ǂݍ���
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
}


// 
void Model::EnemyLoadModel()
{
    // 3D���f���̓ǂݍ���
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel.mv1");
}
