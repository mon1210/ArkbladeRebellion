/**
* @file		SceneManager.h
* @brief	�N���XSceneManager�̐錾�t�@�C��
*/
#pragma once
#include "..\IGameScene\IGameScene.h"
#include "..\Enums.h"
#include "..\GlobalFunctions\GlobalFunctions.h"

class IGameScene;	// �V�[���Ǘ��N���X

class SceneManager
{
public:
	/**
	* @brief SceneManager�̃R���X�g���N�^
	*/
	SceneManager();

	// �f�X�g���N�^
	~SceneManager(void);

	/**
	* @brief �Q�[���S�̂̃V�[����Phase���Ǘ�
	*/
	void manageSceneAndPhase();

	/**
	* @brief �Q�[���S�̂̕`����s���֐�
	*/
	void doDraw();

	/**
	* @brief �V�[���J�ڎ��̃t�F�[�h�A�E�g
	* @note  Title => Game , Game => Title �Ɏg�p
	*/
	void fadeOut(int start_time);
private:
	IGameScene *pScene = nullptr;						// �V�[��
	GamePhase GamePhase = GamePhase::GAMEPHASE_INIT;	// ��ԕϐ�
	int	  startTime = 0;								// FadeOut�J�n���Ԏ擾�p
	float fadeTimer = 0.f;								// �t�F�[�h�^�C�}�[
	float fadeTime = 60.f;								// �t�F�[�h���ԁi�t���[���j
};

