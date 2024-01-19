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
	SceneManager();
	~SceneManager(void);
	void doAnim();										// �Q�[���S�̂̃A�j���[�g
	void doDraw();										// �Q�[���S�̂̕`��
	void fadeOut(int startTime_);						// �V�[���J�ڎ��̃t�F�[�h�A�E�g�����@Todo ������
protected:
	IGameScene *pScene = nullptr;						// �V�[��
	GamePhase GamePhase = GamePhase::GAMEPHASE_INIT;	// ��ԕϐ�
	int	  startTime = 0;								// FadeOut�J�n���Ԏ擾�p
	float fadeTimer = 0.f;								// �t�F�[�h�^�C�}�[
	float fadeTime = 60.f;								// �t�F�[�h���ԁi�t���[���j
};

//	�}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

