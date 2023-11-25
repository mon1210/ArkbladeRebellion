/**
* @file		Selector.h
* @brief	�N���XSelector�̐錾�t�@�C��
*/
#pragma once
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"
// 
#include "Player.h"
// 
#include "Model.h"

//--- �w�b�_�K�[�h�ŁA�����w�b�_�t�@�C����������C���N���[�h����邱�Ƃɂ�����h���ł���
#ifndef __IGAMESCENE_H__
#include "IGameScene.h"
#endif

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
class Player;
class Model;

class Selector
{
public:
	Selector();
	virtual ~Selector(void);
	void doAnim();		//	�Q�[���S�̂̃A�j���[�g
	void doDraw();	//	�Q�[���S�̂̕`��
protected:

	Player* pPlayer;
	IGameScene* pScene;		//	�V�[��
	eGamePhase eGamePhase;	//	��ԕϐ�
	//INT m_iWait;
	INT		count;	//	�J�E���^�[(�f�o�b�O�p)
};

//	�}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

