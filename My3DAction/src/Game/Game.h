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
#include "..\HPBar\HPBar.h"
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
class HPBar;


class Game : public IGameScene
{
public:
	Game(SceneManager* System_);
	~Game(void);
	GameSceneResultCode move() override;	// �Ǘ����\�b�h
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
	SceneManager *pSystem = nullptr;
	Player		 *pPlayer = nullptr;
	Enemy		 *pEnemy = nullptr;
	ModelManager *pModelManager = nullptr;
	Camera		 *pCamera = nullptr;
	BG			 *pBG = nullptr;
	Grid		 *pGrid = nullptr;
	Collision	 *pCollision = nullptr;
	Radar		 *pRadar = nullptr;
	HPBar		 *pHPBar = nullptr;
	StagePhase	 stagePhase = StagePhase::STAGE_INIT;	// ��Ԃ�\��
	bool		 bPause = false;						// �|�[�Y�{�^���A�Ŗh�~�t���O
	int			 timer = 0;
};