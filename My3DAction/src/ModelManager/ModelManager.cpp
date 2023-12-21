#include "ModelManager.h"


/**
* @brief Modelのコンストラクタ
*
*/
ModelManager::ModelManager()
{
    // 3Dモデルの読み込み
    playerHandle = MV1LoadModel("res\\Player\\PlayerModel.mv1");
    enemyHandle = MV1LoadModel("res\\Enemy\\EnemyModel2.mv1");
    tileHandle = MV1LoadModel("res\\test_Tile_model.mv1");

    // unordered_map初期化
    initializeModelList();
}


// デストラクタ
ModelManager::~ModelManager()
{
    MV1DeleteModel(playerHandle);
    MV1DeleteModel(enemyHandle);
    MV1DeleteModel(tileHandle);
}


/**
* @brief unordered_map初期化メソッド　	
* @note  戻り値になる変数を登録
*/
void ModelManager::initializeModelList()
{
    modelList[ModelType::Player] = { playerHandle };
    modelList[ModelType::Enemy]  = { enemyHandle  };
    modelList[ModelType::Tile]   = { tileHandle   };

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
