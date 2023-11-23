/**
* @brief �S�̂̃A�j���[�g���s���֐�
*
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
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "Stage.h"
// �e�N�X�`���ƃr�b�g�}�b�v�̓ǂݍ��݂ƊǗ��Ɋւ���N���X�ƃC���^�[�t�F�[�X���`
#include "TextureLoader.h"


/**
* @brief Selector�̃R���X�g���N�^
*/
Selector::Selector(ID3D11RenderTargetView* pRenderTargetView)
{
	RenderTargetView = pRenderTargetView;
	RenderTargetView->AddRef();

	// �����o������
	count = 0;
	//wait = 0;
	eGamePhase = GAMEPHASE_INIT;
	pScene = NULL;
	//WhiteBrush = NULL;

	// Direct Write ������
	{
		HRESULT hr;
		IDWriteFactory* pFactory;
		 // DirectWrite�t�@�N�g���[����
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pFactory),
			reinterpret_cast<IUnknown**>(&pFactory)
		);
		 // �e�L�X�g�t�H�[�}�b�g����
		hr = pFactory->CreateTextFormat(
			L"consolas",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20,
			L"",
			&TextFormat
		);

		SAFE_RELEASE(pFactory);
	}

	// �e�L�X�g�p�u���V�̐���
	//if (FAILED(RenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::White),
	//	&WhiteBrush
	//))) {
	//	SAFE_RELEASE(WhiteBrush);
	//}
}


// �f�X�g���N�^
Selector::~Selector()
{
	SAFE_DELETE(pScene);
	//SAFE_RELEASE(WhiteBrush);
	//SAFE_RELEASE(RenderTarget);
	SAFE_RELEASE(Device);
	SAFE_RELEASE(Context);
	SAFE_RELEASE(TextFormat);
	SAFE_RELEASE(RenderTargetView);
	TextureLoader::Destroy();
}


/**
* @brief �S�̂̃A�j���[�g���s���֐�
*
*/
void Selector::doAnim() {
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {

	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		eGamePhase = GAMEPHASE_TITLE;	// GAME��Debug
		
	// �^�C�g���V�[��
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Stage(this);
		eGamePhase = GAMEPHASE_GAME;
		
		// �Q�[���V�[��
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			rc = pScene->move();
		else // pScene == NULL
		{
			printf("");		// Debug
		}
		if (rc == GAMESCENE_DEFAULT)
			break;

		eGamePhase = GAMEPHASE_RESET;
	}
	// �f�o�b�O�p�J�E���^
	count++;
}


/**
* @brief �S�̂̕`����s���֐�
*/
void Selector::doDraw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget) {

	// 1�o�C�g�̃r�b�g��(2^8)
	TCHAR	str[256];

	//	�V�[����`��
	if (pScene != NULL)
		pScene->draw(pRenderTargetView, pRenderTarget);
#ifdef _DEBUG
	//	�f�o�b�O�p�\��
	D2D1_SIZE_F size;
	//size = pContext->GetSize();

	//_stprintf_s(str, _countof(str), _T("%08d"), count);
	
	//// ����Ƀ^�C�}�[�\��
	//D2D1_RECT_F	 rc;	// �`��̈�(��ʏ�ł̈ʒu��T�C�Y)���w�肷��ϐ�
	//rc.left = 0;	// �`��̈�̍�����w��
	//rc.top = 0;		//			�V
	//rc.right = size.width;		// �`��̈�̉E�����w��
	//rc.bottom = size.height;	//			�V

	////if (WhiteBrush) {
	////	pRenderTarget->DrawText(str, _tcslen(str), TextFormat, &rc, WhiteBrush);
	////}

#endif
}


/**
* @method
* @brief �Q�[����ʗp��RenderTarget ��Ԃ�
* @note	���̃��\�b�h���Ԃ���  �͕K��Release ���邱��
*/
ID3D11RenderTargetView* Selector::GetRenderTarget() {
	RenderTargetView->AddRef();
	return RenderTargetView;
}


/**
* @method
* @brief �Q�[����ʗp��RenderTarget ��Ԃ�
* @note	���̃��\�b�h���Ԃ���  �͕K��Release ���邱��
*/
ID2D1RenderTarget* Selector::GetRenderTarget2D() {	// �����ŗ�O�G���[
	RenderTarge->AddRef();
	return RenderTarge;
}


/**
* @method
* @brief	�f�o�b�O�p��TextFormat ��Ԃ�
* @note		���̃��\�b�h���Ԃ��� IDWriteTextFormat �͕K��Release ���邱��
*/
IDWriteTextFormat* Selector::GetTextFormat() {
	TextFormat->AddRef();
	return TextFormat;
}