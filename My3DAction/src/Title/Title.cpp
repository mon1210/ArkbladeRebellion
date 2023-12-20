/**
* @file Title.cpp
* @brief �N���X Title �̎���
*/
// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "..\stdafx.h"
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "..\SceneManager\SceneManager.h"
// �^�C�g����ʂ̃Q�[���V�[�����Ǘ�����w�b�_�t�@�C��
#include "Title.h"


/**
* @brief Title�̃R���X�g���N�^
*/
Title::Title(SceneManager *pSystem)
{
	System = pSystem;	//---Select
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
	case TitlePhase::TITLE_INIT:
		titleRunFlag = true;
		Phase = TitlePhase::TITLE_RUN;

		// �^�C�g�����
	case TitlePhase::TITLE_RUN:
	{	//	���ꂪ�Ȃ��� bDone �̏������ŃG���[���ł�
		bool IsDone = false;

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!titleRunFlag) {
				IsDone = true;
				titleRunFlag = true;
			}
		}
		else	// �������Ă��Ȃ���
		{
			titleRunFlag = false;
		}
		// �^�C�g���I���t���OON
		if (IsDone) {
			FadeTimer = TITLE_DONE_TIME;
			Phase = TitlePhase::TITLE_FADE;
		}
		break;
	}

	// �^�C�g���t�F�[�h�A�E�g
	case TitlePhase::TITLE_FADE:
		FadeTimer++;
		// 30�t���[�������ăt�F�[�h�A�E�g
		if (FadeTimer < TITLE_FADEOUT_TIME)
			break;
		Phase = TitlePhase::TITLE_DONE;

		// �^�C�g���I��
	case TitlePhase::TITLE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;
	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


/**
* @brief �`�揈��
* @note	 
*/
void Title::draw()
{
	// Title
	LoadGraphScreen(TITLE_POS_X, TITLE_POS_Y, "res\\test_title_background.png", TRUE);
	// press space
	LoadGraphScreen(TITLE_PS_POS_X, TITLE_PS_POS_Y, "res\\test_title_press_space.png", TRUE);

	switch (Phase) 
	{
	case TitlePhase::TITLE_FADE:
	case TitlePhase::TITLE_DONE:
		System->fadeOut();
	}

}