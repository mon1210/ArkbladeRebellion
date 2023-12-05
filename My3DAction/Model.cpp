
#include "Model.h"


/**
* @brief Modelのコンストラクタ
*
*/
Model::Model()
{
    enemyHandle = 0;
    playerHandle = 0;
    tileHandle = 0;

}


// デストラクタ
Model::~Model()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief プレイヤーモデル読み込み関数
*/
void Model::LoadModel()
{
    // 3Dモデルの読み込み
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


/**
* @brief プレイヤーモデル取得用関数
*/
int Model::GetPlayerModel()
{
    return playerHandle;
}


/**
* @brief エネミーモデル取得用関数
*/
int Model::GetEnemyModel()
{
    return enemyHandle;
}


/**
* @brief タイルモデル取得用関数
*/
int Model::GetTileModel()
{
    return tileHandle;
}
