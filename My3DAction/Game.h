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
	~Game(void);
	GameSceneResultCode move() override;	// �A�j���[�V����(1�t���[��)�̎��s
	void draw() override;					// �`�惁�\�b�h
	ModelManager *GetModelManager();		// Model���擾���ĕԂ�
	Collision *GetCollision();				// Collision���擾���ĕԂ�
	Radar *GetRadar();						// Radar���擾���ĕԂ�
	BG	*GetBG();							// BG���擾���ĕԂ�
	Player *GetPlayer();					// Player���擾���ĕԂ�
	Camera *GetCamera();					// Camera���擾���ĕԂ�
protected:
	SceneManager *System = NULL;
	Player		 *pPlayer = NULL;
	Enemy		 *pEnemy = NULL;
	ModelManager *pModelManager = NULL;
	Camera		 *pCamera = NULL;
	BG			 *pBG = NULL;
	Grid		 *pGrid = NULL;
	Collision	 *pCollision = NULL;
	Radar		 *pRadar = NULL;
	StagePhase	 Phase = STAGE_INIT;
	bool		 bPause = false;			//	�|�[�Y�{�^���A�Ŗh�~�t���O
	int			 Timer = 0;
};