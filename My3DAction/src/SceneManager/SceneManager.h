/**
* @file		SceneManager.h
* @brief	�N���X SceneManager �̐錾
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

	/**
	* @brief SceneManager�̃f�X�g���N�^
	*/
	~SceneManager();

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
	* @param[in] start_time �t�F�[�h�A�E�g�J�n����
	*/
	void fadeOut(int start_time);
private:
	//! �V�[��
	IGameScene *pScene = nullptr;
	//! ��ԕϐ�
	GamePhase GamePhase = GamePhase::GAMEPHASE_INIT;
	//! FadeOut�J�n���Ԏ擾�p
	int	  startTime = 0;
	//! �t�F�[�h�^�C�}�[
	float fadeTimer = 0.f;
	//! �t�F�[�h���ԁi�t���[��
	float fadeTime = 60.f;
};

