/**
* @file Stage.h
* @brief 
*/
#pragma once
#include "Selector.h"
#include <list>

//--- �w�b�_�K�[�h�œ����t�@�C������x�C���N���[�h����邱�Ƃ�h���ł���
#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class Player;
class Enemy;
class BG;
class Grid;

enum StagePhase {
	STAGE_INIT = 0,
	STAGE_RUN = 1,
	STAGE_PAUSE = 2,
	STAGE_FADE = 3,
	STAGE_DONE = 4,
};

class Stage : public IGameScene
{
public:
	Stage(Selector* pSystem);
	virtual ~Stage(void);
	virtual GameSceneResultCode move() override;
	virtual void draw() override;
protected:
	Selector*	System;
	Player*		pPlayer;
	Enemy*		pEnemy;
	BG*			pBG;
	Grid*		pGrid;
	StagePhase	Phase;
	bool		bPause;		//	�|�[�Y�{�^���A�Ŗh�~�t���O
	int		Timer;
};