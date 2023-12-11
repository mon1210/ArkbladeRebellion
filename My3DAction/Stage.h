/**
* @file		Stage.h
* @brief	�N���X Stage �̐錾
*/
#pragma once
#include "SceneManager.h"
#include "BG.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Model.h"
#include "Grid.h"
#include "Collision.h"
#include "Radar.h"
#include "Constants.h"
#include "IGameObject.h"

// �N���X�̑O���錾
class SceneManager;
class Player;
class Enemy;
class Model;
class Camera;
class BG;
class Grid;
class Collision;
class Radar;

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
	Stage(SceneManager* pSystem);
	virtual ~Stage(void);
	virtual GameSceneResultCode move() override;	// �A�j���[�V����(1�t���[��)�̎��s
	virtual void draw() override;		// �`�惁�\�b�h
	virtual Collision *GetCollision();	// �����蔻��p��Collision��Ԃ�
	virtual Radar *GetRadar();			// �����蔻��p��Radar��Ԃ�
protected:
	SceneManager*System;
	Player		*pPlayer;
	Enemy		*pEnemy;
	Model		*pModel;
	Camera		*pCamera;
	BG			*pBG;
	Grid		*pGrid;
	Collision	*pCollision;
	Radar		*pRadar;
	StagePhase	Phase;
	bool		bPause;		//	�|�[�Y�{�^���A�Ŗh�~�t���O
	int			Timer;
	int			tileHandle;
};