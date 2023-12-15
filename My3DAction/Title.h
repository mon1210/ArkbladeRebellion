/**
* @file		Title.h
* @brief	�N���X Title �̐錾
*/
#pragma once
#include "Constants.h"
#include "IGameScene.h"

enum TitlePhase {
	TITLE_INIT = 0,
	TITLE_RUN = 1,
	TITLE_FADE = 2,
	TITLE_DONE = 3
};

// �N���X�̑O���錾
class SceneManager;

class Title : public IGameScene
{
public:
	Title(SceneManager *pSystem);
	virtual ~Title();
	virtual GameSceneResultCode move() override;	// �A�j���[�V�������\�b�h�@GAMESCENE_DEFAULT:�p�� / GAMESCENE_END_OK:�Q�[���J�n
	virtual void draw() override;					// �`�惁�\�b�h

protected:
	SceneManager *System = NULL;
	TitlePhase	Phase = TITLE_INIT;
	bool	titleRunFlag = false;					// Title�̏�Ԃ��Ǘ�����flag
	INT		FadeTimer = 0;
};

