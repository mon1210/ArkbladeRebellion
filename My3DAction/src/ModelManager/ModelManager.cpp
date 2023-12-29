#include "ModelManager.h"


/**
* @brief Modelのコンストラクタ
*
*/
ModelManager::ModelManager()
{
    // unordered_map初期化
    initializeModelList();
}


// デストラクタ
ModelManager::~ModelManager()
{
}


/**
* @brief unordered_map初期化メソッド　	
* @note  戻り値になる変数を登録
*/
void ModelManager::initializeModelList()
{
    modelList[ModelType::Player] = { MV1LoadModel("res\\Player\\PlayerModel.mv1") };
    modelList[ModelType::Enemy]  = { MV1LoadModel("res\\Enemy\\EnemyModel2.mv1") };
    modelList[ModelType::Tile]   = { MV1LoadModel("res\\test_Tile_model.mv1") };
}


/**
* @brief モデルを取得して返す
*/
int ModelManager::GetHandle(ModelType type_)
{
    // リストが空でないとき
    if (modelList.count(type_) > 0)
    {
        return modelList[type_];
    }

    return modelList[ModelType::No];
}
