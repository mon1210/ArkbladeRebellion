#include "Title.h"


// �R���X�g���N�^
Title::Title(SceneManager *System)
{
	pSystem = System;
}


// �f�X�g���N�^
Title::~Title()
{
}


// �Ǘ����\�b�h
GameSceneResultCode Title::move()
{
	switch (Phase) {
		// �^�C�g���J�n
	case TitlePhase::TITLE_INIT:
		Phase = TitlePhase::TITLE_RUN;

		// �^�C�g�����
	case TitlePhase::TITLE_RUN:
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			fadeTimer = TITLE_DONE_TIME;
			Phase = TitlePhase::TITLE_FADE;
		}
		break;
	}

	// �^�C�g���t�F�[�h�A�E�g
	case TitlePhase::TITLE_FADE:
		if (fadeTimer++ < TITLE_FADEOUT_TIME)
			break;
		Phase = TitlePhase::TITLE_DONE;

		// �^�C�g���I��
	case TitlePhase::TITLE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;
	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


// �`�揈��
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
		if (!isFadeStart) 
		{ 
			startTime = GetNowCount(); 
			isFadeStart = true; 
		}
		pSystem->fadeOut(startTime);
		break;
	}

}