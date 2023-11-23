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
void Model::ModelSet()
{
    // ‚R‚cƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel.mv1");
    // 
    playerHandle = MV1LoadModel("res\Player\PlayerModel.mv1");

}
