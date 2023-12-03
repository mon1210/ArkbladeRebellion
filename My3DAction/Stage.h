/**
* @file		Stage.h
* @brief	�N���X Stage �̐錾
*/
#pragma once
#include "Selector.h"
#include "IGameObject.h"

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
	virtual GameSceneResultCode move() override;	// �A�j���[�V����(1�t���[��)�̎��s
	virtual void draw() override;	// �`�惁�\�b�h
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