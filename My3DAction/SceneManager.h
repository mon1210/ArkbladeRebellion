/**
* @file		SceneManager.h
* @brief	�N���XSceneManager�̐錾�t�@�C��
*/
#pragma once
#include "IGameScene.h"

enum eGamePhase {
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200
};

enum GameSceneResultCode {
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

class IGameScene;	// �V�[���Ǘ��N���X

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager(void);
	void doAnim();							// �Q�[���S�̂̃A�j���[�g
	void doDraw();							// �Q�[���S�̂̕`��
	void FadeOut();							// �V�[���J�ڎ��̃t�F�[�h�A�E�g�����@Todo ������
	int Clamp(int value, int min, int max)	// �l���w�肳�ꂽ�͈͓��Ɏ��߂郁�\�b�h
	{
		if (value < min)return min; 
		else if (value > max)return max;
		else return value;
	}
protected:
	IGameScene *pScene = NULL;				//	�V�[��
	eGamePhase eGamePhase = GAMEPHASE_INIT;	//	��ԕϐ�
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

