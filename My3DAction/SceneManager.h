/**
* @file		SceneManager.h
* @brief	�N���XSceneManager�̐錾�t�@�C��
*/
#pragma once
#include "IGameScene.h"
#include "Enums.h"

class IGameScene;	// �V�[���Ǘ��N���X

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager(void);
	void doAnim();							// �Q�[���S�̂̃A�j���[�g
	void doDraw();							// �Q�[���S�̂̕`��
	void fadeOut();							// �V�[���J�ڎ��̃t�F�[�h�A�E�g�����@Todo ������
	int clamp(int value, int min, int max)	// �l���w�肳�ꂽ�͈͓��Ɏ��߂郁�\�b�h
	{
		if (value < min)return min; 
		else if (value > max)return max;
		else return value;
	}
protected:
	IGameScene *pScene = NULL;				//	�V�[��
	GamePhase GamePhase = GAMEPHASE_INIT;	//	��ԕϐ�
	int fadeTimer = 0;						// �t�F�[�h�^�C�}�[
	int fadeTime = 0;						// �t�F�[�h���ԁi�t���[���j
	int startTime = 0;						// �J�n����
};

//	�}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

