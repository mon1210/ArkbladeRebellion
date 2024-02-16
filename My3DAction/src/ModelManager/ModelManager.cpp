#include "ModelManager.h"


/**
* @brief Modelのコンストラクタ
*/
ModelManager::ModelManager()
{
    // unordered_map初期化
    initializeModelList();
}


// デストラクタ
ModelManager::~ModelManager()
{
    // モデルを解放
    for (auto& entry : modelList)
    {
        MV1DeleteModel(entry.second);
    }
}


/**
* @brief unordered_map初期化メソッド　	
* @note  登録と同時にZBufferも適用する
*/
void ModelManager::initializeModelList()
{
    modelList[ModelType::Player]          = { MV1LoadModel("res\\Player\\PlayerModel.mv1") };
    modelList[ModelType::PlayerWithSword] = { MV1LoadModel("res\\Player\\PlayerModelWithSword.mv1") };
    modelList[ModelType::Enemy]           = { MV1LoadModel("res\\Enemy\\EnemyModel2.mv1") };
    modelList[ModelType::Tile]            = { MV1LoadModel("res\\test_Tile_model.mv1") };

    // モデルにZBufferを適用する
    for (auto& entry : modelList)
    {
        //「entry」キーを示す  「entry.second」=> MV1LoadModel("");
        MV1SetUseZBuffer(entry.second, TRUE);
    }
}


/**
* @brief モデルを取得して返す
*/
int ModelManager::GetHandle(ModelType type)
{
    // リストが空でないとき
    if (modelList.count(type) > 0)
    {
        return modelList[type];
    }

    return -1;
}
