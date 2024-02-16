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
	/**
	* @brief Title�̃R���X�g���N�^
	*/
	Title(SceneManager *System);
	~Title();

	/**
	* @brief  �Ǘ����\�b�h
	* @return GAMESCENE_DEFAULT:�p�� / GAMESCENE_END_OK:�Q�[���J�n
	*/
	GameSceneResultCode move() override;

	/**
	* @brief �`�揈��
	*/
	void draw() override;
private:
	SceneManager *pSystem = nullptr;
	TitlePhase	Phase = TitlePhase::TITLE_INIT;		// ��Ԃ�\��
	int		startTime = 0;							// FadeOut�J�n���Ԏ擾�p
	int		fadeTimer = 0;
	bool	isFadeStart = false;					// FadeOut���J�n�������ǂ�����flag
};

