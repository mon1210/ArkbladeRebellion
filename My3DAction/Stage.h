/**
* @file		Stage.h
* @brief	�N���X Stage �̐錾
*/
#pragma once
#include "Selector.h"
#include "BG.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Model.h"
#include "Grid.h"
#include "Collider.h"
#include "Constants.h"
#include "IGameObject.h"

// �N���X�̑O���錾
class Selector;
class Player;
class Enemy;
class Model;
class Camera;
class BG;
class Grid;
class Collider;

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
	Stage(Selector *pSystem);
	virtual ~Stage(void);
	virtual GameSceneResultCode move() override;	// �A�j���[�V����(1�t���[��)�̎��s
	virtual void draw() override;		// �`�惁�\�b�h
	virtual Collider *GetCollider();	// �����蔻��p��Collider��Ԃ�
protected:
	Selector	*System;
	Player		*pPlayer;
	Enemy		*pEnemy;
	Model		*pModel;
	Camera		*pCamera;
	BG			*pBG;
	Grid		*pGrid;
	Collider	*pCollider;
	StagePhase	Phase;
	bool		bPause;		//	�|�[�Y�{�^���A�Ŗh�~�t���O
	int			Timer;
	int			tileHandle;
};