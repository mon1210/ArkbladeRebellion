// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[���̔w�i���Ǘ�����N���X�Ɗ֘A�f�[�^���`
#include "BG.h"
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

}


// �f�X�g���N�^
BG::~BG()
{
}


/**
* @brief �`�惁�\�b�h
* @note  ��ʏ�Ɍ����Ă��镔���̂ݕ`��
*/
void BG::draw() 
{
}