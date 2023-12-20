/**
* @file		Game.h
* @brief	�N���X Game �̐錾
*/
#pragma once
#include "..\SceneManager\SceneManager.h"
#include "..\BG\BG.h"
#include "..\Player\Player.h"
#include "..\Enemy\Enemy.h"
#include "..\Enums.h"
#include "..\Camera\Camera.h"
#include "..\ModelManager\ModelManager.h"
#include "..\Grid\Grid.h"
#include "..\Collision\Collision.h"
#include "..\Radar\Radar.h"
#include "..\UI\UI.h"
#include "..\Constants.h"

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
class UI;


class Game : public IGameScene
{
public:
	Game(SceneManager* System_);
	~Game(void);
	GameSceneResultCode move() override;	// �A�j���[�V����(1�t���[��)�̎��s
	void draw() override;					// �`�惁�\�b�h
	// �ȉ��擾�p�萔=================================================== //
	Player			*GetPlayer();			// Player���擾���ĕԂ�
	Enemy			*GetEnemy();			// Enemy���擾���ĕԂ�
	ModelManager	*GetModelManager();		// Model���擾���ĕԂ�
	Camera			*GetCamera();			// Camera���擾���ĕԂ�
	BG				*GetBG();				// BG���擾���ĕԂ�
	Collision		*GetCollision();		// Collision���擾���ĕԂ�
	Radar			*GetRadar();			// Radar���擾���ĕԂ�
	// �ȏ�擾�p�萔=================================================== //
protected:
	SceneManager *pSystem = NULL;
	Player		 *pPlayer = NULL;
	Enemy		 *pEnemy = NULL;
	ModelManager *pModelManager = NULL;
	Camera		 *pCamera = NULL;
	BG			 *pBG = NULL;
	Grid		 *pGrid = NULL;
	Collision	 *pCollision = NULL;
	Radar		 *pRadar = NULL;
	UI			 *pUI = NULL;
	StagePhase	 Phase = STAGE_INIT;		// ��Ԃ�\��
	bool		 bPause = false;			// �|�[�Y�{�^���A�Ŗh�~�t���O
	int			 Timer = 0;
};