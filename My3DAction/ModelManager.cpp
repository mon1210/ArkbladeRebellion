#include "ModelManager.h"


/**
* @brief Modelのコンストラクタ
*
*/
ModelManager::ModelManager()
{
    // 3Dモデルの読み込み
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


// デストラクタ
ModelManager::~ModelManager()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief プレイヤーモデルを取得して返す
*/
int ModelManager::GetPlayerModel()
{
    return playerHandle;
}


/**
* @brief エネミーモデルを取得して返す
*/
int ModelManager::GetEnemyModel()
{
    return enemyHandle;
}


/**
* @brief タイルモデルを取得して返す
*/
int ModelManager::GetTileModel()
{
    return tileHandle;
}
