/**
* @file		Game.h
* @brief	�N���X Game �̐錾
*/
#pragma once
#include "SceneManager.h"
#include "BG.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "ModelManager.h"
#include "Grid.h"
#include "Collision.h"
#include "Radar.h"
#include "Constants.h"

// �N���X�̑O���錾
class SceneManager;
class Player;
class Enemy;
class ModelManager;
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

class Game : public IGameScene
{
public:
	Game(SceneManager* pSystem);
	virtual ~Game(void);
	virtual GameSceneResultCode move() override;	// �A�j���[�V����(1�t���[��)�̎��s
	virtual void draw() override;					// �`�惁�\�b�h
	virtual ModelManager *GetModelManager();		// 
	virtual Collision *GetCollision();				// �����蔻��p��Collision��Ԃ�
	virtual Radar *GetRadar();						// �����蔻��p��Radar��Ԃ�
	virtual BG	*GetBG();							// 
protected:
	SceneManager *System;
	Player		 *pPlayer;
	Enemy		 *pEnemy;
	ModelManager *pModelManager;
	Camera		 *pCamera;
	BG			 *pBG;
	Grid		 *pGrid;
	Collision	 *pCollision;
	Radar		 *pRadar;
	StagePhase	 Phase;
	bool		 bPause;		//	�|�[�Y�{�^���A�Ŗh�~�t���O
	int			 Timer;
};