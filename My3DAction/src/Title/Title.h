/**
* @file		Title.h
* @brief	�N���X Title �̐錾
*/
#pragma once
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\IGameScene\IGameScene.h"

//! �N���X�̑O���錾
class SceneManager;

class Title : public IGameScene
{
public:
	/**
	* @brief Title�̃R���X�g���N�^
	*/
	Title(SceneManager *System);

	/**
	* @brief Title�̃f�X�g���N�^
	*/
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
	//! ��Ԃ�\��
	TitlePhase	Phase = TitlePhase::TITLE_INIT;
	//! FadeOut�J�n���Ԏ擾�p
	int		startTime = 0;
	//! FadeOut�o�ߎ���
	int		fadeTimer = 0;
	//! FadeOut���J�n�������ǂ�����flag
	bool	isFadeStart = false;
};

