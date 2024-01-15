#include "BG.h"

/**
* @brief BG�̃R���X�g���N�^
*/
BG::BG(Game *Game_)
{
	if (Game_)
		tileHandle = Game_->GetModelManager()->GetHandle(ModelType::Tile);
}


// �f�X�g���N�^
BG::~BG()
{
}


/**
* @brief �����f�����擾���ĕԂ�
*/
int BG::GetModelHandle()
{
	return tileHandle;
}


/**
* @brief �`�惁�\�b�h
* @note  ��ʏ�Ɍ����Ă��镔���̂ݕ`��
*/
void BG::draw() 
{
	// 3D���f���ɍ��W���Z�b�g
	MV1SetPosition(tileHandle, position);

	// 3D���f���̕`��
	MV1DrawModel(tileHandle);

}