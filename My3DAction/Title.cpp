/**
* @file Title.cpp
* @brief �N���X Title �̎���
*/

// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// Direct2D�̃w�b�_�t�@�C�����C���N���[�h
#include <d2d1.h>
// DirectWrite �w�b�_�[�t�@�C�����C���N���[�h
#include <dwrite.h>
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "Selector.h"
// �^�C�g����ʂ̃Q�[���V�[�����Ǘ�����w�b�_�t�@�C��
#include "Title.h"
// �e�N�X�`���ƃr�b�g�}�b�v�̓ǂݍ��݂ƊǗ��Ɋւ���N���X�ƃC���^�[�t�F�[�X���`
#include "TextureLoader.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"


/**
* @brief Title�̃R���X�g���N�^
*/
Title::Title(Selector* pSystem)
{
	ID3D11RenderTargetView* pTarget;

	System = pSystem;	//---Select
	Phase = TITLE_INIT;	//---TitlePhase
	Timer = 0;			//---INT
	FadeTimer = 0;		//---INT
	pImage = NULL;		//---ID2D1Bitmap
	pImage2 = NULL;		//---ID2D1Bitmap
	Black = NULL;		//---ID2D1SolidColorBrush

	//pTarget = pSystem->GetRenderTarget();
	//if (pTarget) {
	//	// �摜���������ɓǂݍ���
	//	TextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\title_background.png"), &m_pImage);
	//	TextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\title_string.png"), &m_pImage2);
	//	TextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\title_press_space.png"), &m_pImage3);
	//	pTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlack);
	//	pTarget->Release();
	//	pTarget = NULL;
	//}
}


// �f�X�g���N�^
Title::~Title()
{
	SAFE_RELEASE(pImage);
	SAFE_RELEASE(pImage2);
	SAFE_RELEASE(pImage3);
	SAFE_RELEASE(Black);
}


/**
* @brief �A�j���[�V�������\�b�h
* @return GAMESCENE_DEFAULT:�p�� / GAMESCENE_END_OK:�Q�[���J�n
*/
GameSceneResultCode Title::move()
{
	switch (Phase) {
		// �^�C�g���J�n
	case TITLE_INIT:
		Timer = TITLE_TIMER_INIT;
		Flag = true;
		Phase = TITLE_RUN;

		// �^�C�g�����
	case TITLE_RUN:
	{	//	���ꂪ�Ȃ��� bDone �̏������ŃG���[���ł�
		bool bDone = false;
		Timer++;

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!Flag) {
				bDone = true;
				Flag = true;
			}
		}
		else	// �������Ă��Ȃ���
		{
			Flag = false;
		}
		// �^�C�g���I���t���OON
		if (bDone) {
			FadeTimer = TITLE_DONE_TIME;
			Phase = TITLE_FADE;
		}
		break;
	}

	// �^�C�g���t�F�[�h�A�E�g
	case TITLE_FADE:
		FadeTimer++;
		// 30�t���[�������ăt�F�[�h�A�E�g
		if (FadeTimer < TITLE_FADEOUT_TIME)
			break;
		Phase = TITLE_DONE;

		// �^�C�g���I��
	case TITLE_DONE:
		return GAMESCENE_END_OK;
	}

	return GAMESCENE_DEFAULT;
}


/**
* @brief �`�揈��
* @note	 
*/
void Title::draw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget)
{
	printf("Title");

}