// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// Direct2D�̃w�b�_�t�@�C�����C���N���[�h
#include <d2d1.h>
// �Q�[���̔w�i���Ǘ�����N���X�Ɗ֘A�f�[�^���`
#include "BG.h"
// �e�N�X�`���ƃr�b�g�}�b�v�̓ǂݍ��݂ƊǗ��Ɋւ���N���X�ƃC���^�[�t�F�[�X���`
#include "TextureLoader.h"
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
BG::BG(ID2D1RenderTarget * pRenderTarget)
{

	TextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Title_background.png"), &BGImage);

}


// 
BG::~BG()
{

	SAFE_DELETE(BGImage);

}


/**
* @brief �`�惁�\�b�h
* @note  ��ʏ�Ɍ����Ă��镔���̂ݕ`��
*/
void BG::draw(ID2D1RenderTarget* pRenderTarget) 
{

	// �ȉ��w�i�`�揈�� ============================================
	//D2D1_SIZE_F size;
	D2D1_RECT_F rc,		// �`��̈�(��ʏ�ł̈ʒu��T�C�Y)���w�肷��ϐ�
				src;	// �e�N�X�`���̒��ł̍��W���w�肵�A�e�N�X�`�������肷��ϐ�
	//size = pRenderTarget->GetSize();
	// �`��̈�̐ݒ�
	rc.left = 0.f; rc.top = 0.f;	// �`��̈�̍�����w��
	rc.right = WINDOW_WIDTH_SIZE; rc.bottom = WINDOW_HEIGHT_SIZE;		// �`��̈�̉E�����w��

	// �e�N�X�`�����W�̌v�Z
	src.left = 0.f; src.top = 0.f;		// �e�N�X�`�����W�̍�����w��
	src.right = src.left + WINDOW_WIDTH_SIZE; src.bottom = WINDOW_HEIGHT_SIZE;	// �e�N�X�`�����W�̉E�����w��

	// �w�i�̕`��
	pRenderTarget->DrawBitmap(BGImage, rc, BG_SCALE_FACTOR, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
	 
	// �ȏ�w�i�`�揈�� ============================================



}