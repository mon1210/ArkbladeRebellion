#include "ModelManager.h"


// �R���X�g���N�^
ModelManager::ModelManager()
{
    // unordered_map������
    initializeModelList();
}


// �f�X�g���N�^
ModelManager::~ModelManager()
{
    // ���f�������
    for (auto& entry : modelList)
    {
        MV1DeleteModel(entry.second);
    }
}


// unordered_map���������\�b�h
void ModelManager::initializeModelList()
{
    modelList[ModelType::Player]          = { MV1LoadModel("res\\Player\\PlayerModel.mv1") };
    modelList[ModelType::PlayerWithSword] = { MV1LoadModel("res\\Player\\PlayerModelWithSword.mv1") };
    modelList[ModelType::Enemy]           = { MV1LoadModel("res\\Enemy\\EnemyModel.mv1") };
    modelList[ModelType::Tile]            = { MV1LoadModel("res\\test_Tile_model.mv1") };

    // ���f����ZBuffer��K�p����
    for (auto& entry : modelList)
    {
        //�uentry�v�L�[������  �uentry.second�v=> MV1LoadModel("");
        MV1SetUseZBuffer(entry.second, TRUE);
    }
}


// ���f�����擾���ĕԂ�
int ModelManager::GetHandle(ModelType type)
{
    // ���X�g����łȂ��Ƃ�
    if (modelList.count(type) > 0)
    {
        return modelList[type];
    }

    return -1;
}
