// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[���̔w�i���Ǘ�����N���X�Ɗ֘A�f�[�^���`
#include "BG.h"
// 
#include "Model.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"


//  �}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }


/**
* @brief BG�̃R���X�g���N�^
*/
BG::BG()
{
	tile_handle = 0;
	pModel = NULL;
	position = VGet(0.f, 0.f, 0.f);

	pModel = new Model();
	// ���f���擾
	pModel->LoadTileModel();
	tile_handle = pModel->GetTileModel();

}


// �f�X�g���N�^
BG::~BG()
{
}


/**
* @brief �^�C�g�����f���擾�p�֐�
* @note
*/
int BG::GetModelHandle()
{
	return tile_handle;
}


/**
* @brief �`�惁�\�b�h
* @note  ��ʏ�Ɍ����Ă��镔���̂ݕ`��
*/
void BG::draw() 
{
	// 3D���f���ɍ��W���Z�b�g
	MV1SetPosition(tile_handle, position);

	// 3D���f���̕`��
	MV1DrawModel(tile_handle);

}