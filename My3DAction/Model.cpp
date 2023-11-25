
#include "DxLib.h"
#include "Constants.h"
#include "Model.h"


/**
* @brief Modelのコンストラクタ
*
*/
Model::Model()
{
    enemyHandle = 0;
    playerHandle = 0;

}


// デストラクタ
Model::~Model()
{
}


/**
* @brief プレイヤーモデル読み込み関数
*/
void Model::PlayerLoadModel()
{
    // 3Dモデルの読み込み
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
}


/**
* @brief  エネミーモデル読み込み関数
*/
void Model::EnemyLoadModel()
{
    // 3Dモデルの読み込み
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
}
