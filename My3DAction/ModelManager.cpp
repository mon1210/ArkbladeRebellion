#include "ModelManager.h"


/**
* @brief Modelのコンストラクタ
*
*/
ModelManager::ModelManager()
{
    loadModel();
}


// デストラクタ
ModelManager::~ModelManager()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief モデル読み込みメソッド
*/
void ModelManager::loadModel()
{
    // 3Dモデルの読み込み
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


/**
* @brief プレイヤーモデルを取得して返す
*/
int ModelManager::getPlayerModel()
{
    return playerHandle;
}


/**
* @brief エネミーモデルを取得して返す
*/
int ModelManager::getEnemyModel()
{
    return enemyHandle;
}


/**
* @brief タイルモデルを取得して返す
*/
int ModelManager::getTileModel()
{
    return tileHandle;
}
