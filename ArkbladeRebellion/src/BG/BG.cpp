#include "BG.h"


// �R���X�g���N�^
BG::BG(Game *Game)
{
	if (Game)
		tileHandle = Game->GetModelManager()->GetHandle(ModelType::Tile);
}


// �f�X�g���N�^
BG::~BG()
{
}


// �����f�����擾���ĕԂ�
int BG::GetModelHandle()
{
	return tileHandle;
}


// �`�惁�\�b�h
void BG::draw() 
{
	// 3D���f���ɍ��W���Z�b�g
	MV1SetPosition(tileHandle, position);

	// 3D���f���̕`��
	MV1DrawModel(tileHandle);

}