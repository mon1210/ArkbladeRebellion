/**
* @file Title.cpp
* @brief �N���X Title �̎���
*/
// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "SceneManager.h"
// �^�C�g����ʂ̃Q�[���V�[�����Ǘ�����w�b�_�t�@�C��
#include "Title.h"


/**
* @brief Title�̃R���X�g���N�^
*/
Title::Title(SceneManager *pSystem)
{
	System = pSystem;	//---Select
	Phase = TITLE_INIT;	//---TitlePhase
	Timer = 0;			//---INT
	FadeTimer = 0;		//---INT
}


// �f�X�g���N�^
Title::~Title()
{
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



void SceneFadeOut(int TmpValue)
{


	SetDrawScreen(DX_SCREEN_BACK);

	//�t�F�[�h�l�̐ݒ�i0�`255�̒l���L���j
	TmpValue = 255;		// �ϐ����ύX Todo

	while(1)
	{
		ClearDrawScreen(); // ����ʂ̃f�[�^��S�č폜

		if (TmpValue < 256) 
		{
			SetDrawBright(TmpValue, TmpValue, TmpValue);
		}

		TmpValue--;

		// 0�ŏI��
		if (TmpValue == 0) 
		{
			break;
		}

		// �G���[���
		if (ProcessMessage() == -1) 
		{
			break;
		}

		ScreenFlip();
	}

}

int tmp = 255;

/**
* @brief �`�揈��
* @note	 
*/
void Title::draw()
{
	// Title
	LoadGraphScreen(0, 0, "res\\test_title_background.png", TRUE);
	// press space
	LoadGraphScreen(20, 240, "res\\test_title_press_space.png", TRUE);

	switch (Phase) 
	{
	case TITLE_FADE:
	case TITLE_DONE:
		while (tmp >= 0)
		{
			SceneFadeOut(tmp);
			tmp--;
		}
	}

}