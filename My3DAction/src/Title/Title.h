/**
* @file		Title.h
* @brief	�N���X Title �̐錾
*/
#pragma once
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\IGameScene\IGameScene.h"

// �N���X�̑O���錾
class SceneManager;

class Title : public IGameScene
{
public:
	Title(SceneManager *pSystem);
	~Title();
	GameSceneResultCode move() override;			// �Ǘ����\�b�h�@GAMESCENE_DEFAULT:�p�� / GAMESCENE_END_OK:�Q�[���J�n
	void draw() override;							// �`�惁�\�b�h

protected:
	SceneManager *System = nullptr;
	TitlePhase	Phase = TitlePhase::TITLE_INIT;		// ��Ԃ�\��
	bool	titleRunFlag = false;					// Title�̏�Ԃ��Ǘ�����flag
	INT		FadeTimer = 0;
};

