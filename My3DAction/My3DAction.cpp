/**
* @file		My3DAction.cpp
* @author	R.Monda
* @date		..2023
* @brief	�V�[���Ǘ��N���X		: Selector	(Selector.h)
*			�Q�[���V�[���N���X		: Stage		(Stage.h)
*			�v���C���[�N���X		: Player	(Player.h)
*			�w�i�E�}�b�v�N���X		: BG		(BG.h)
* @note		�G���[���o���ۂ́A�v���W�F�N�g�̃v���p�e�B���J���A
*			C/C++	 -> �S�� -> �ǉ��̃C���N���[�h�f�B���N�g����'Lib;%(AdditionalIncludeDirectories)'��ǉ����� ����
*			�����J�[ -> �S�� -> �ǉ��̃��C�u�����f�B���N�g����'Lib;%(AdditionalIncludeDirectories)'��ǉ����� ����
*			�����J�[ -> ���� -> �ǉ��̈ˑ��t�@�C����'d3d11.lib'��ǉ����Ă�������
*/

// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// CRT �f�o�b�O�w�b�_�t�@�C�����C���N���[�h
#include <crtdbg.h>
// TCHAR �^�C�v��}�N�����`�����w�b�_�t�@�C�����C���N���[�h
#include <tchar.h>
// �W�����o�͊֐���񋟂��� C ���C�u�����w�b�_�t�@�C�����C���N���[�h
#include <stdio.h>
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "Selector.h"
// 
#include "BG.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"


#define MAX_LOADSTRING 100

#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if(o){ delete [] (o); o = NULL; }

#define FPS 60.0
#define INTERVAL (1.0/FPS)

Selector* g_pSelector = NULL;	//	�Q�[���V�X�e���I�u�W�F�N�g
BG* g_BG = NULL;

/**
* @fn
* @brief	�A�v���P�[�V�����̃G���g���[�|�C���g
*/
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	//! �f�o�b�O�p�̃t���O�Z�b�g
	//--- �������f�o�b�O���s�����߂Ɏg�p����� _Crt ���C�u�����̊֐�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ChangeWindowMode(TRUE);     // �E�B���h�E���[�h�ɐݒ�
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_COLOR);    // �E�B���h�E�ݒ�

	/*********************
		1.����������
	*********************/

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[�����������璼���ɏI��
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);	// �`��Ώۂ𗠂̃L�����o�X�Ɏw��

	// �J�����̕`�拗��   SetCameraNearFar(�ŒZ����,�Œ�����)
	SetCameraNearFar(0.f, 1000.f);

	//	�Q�[���V�X�e��������
	g_pSelector = new Selector();

	g_BG = new BG();

	// Tile�ɓ����蔻��t�^
	int tile_handle = g_BG->GetModelHandle();
	MV1SetupCollInfo(
		tile_handle,		// �����蔻���ݒ肷�郂�f���̃n���h��
		-1,					// �ΏۂƂȂ郂�f���̃t���[���ԍ�(-1�͑S��)	
		32,					// X���̋�ԕ�����
		32,					// Y���̋�ԕ�����
		32					// Z���̋�ԕ�����
	);

	/**************************
		2.���b�Z�[�W���[�v
	**************************/
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

		// �w�i�̐F�ύX�@���F
		SetBackgroundColor(0, 0, 0);

		// �N���A�֐�
		ClearDrawScreen();

		//	���̒��ɕ`�揈��������

		if (g_pSelector)
			g_pSelector->doAnim();

		if (g_pSelector)
			g_pSelector->doDraw();

		//	���̒��ɕ`�揈��������

		// �t���b�v�֐�
		ScreenFlip();

	}

	/**************************
			3.�I������
	**************************/

	SAFE_DELETE(g_pSelector);
	SAFE_DELETE(g_BG);

	// DX���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
