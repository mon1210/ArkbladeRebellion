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
* @brief モデル読み込みメソッド
*/
void Model::loadModel()
{
    // 3Dモデルの読み込み
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel2.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");
}


/**
* @brief プレイヤーモデルを取得して返す
*/
int Model::getPlayerModel()
{
    return playerHandle;
}


/**
* @brief エネミーモデルを取得して返す
*/
int Model::getEnemyModel()
{
    return enemyHandle;
}


/**
* @brief タイルモデルを取得して返す
*/
int Model::getTileModel()
{
    return tileHandle;
}
