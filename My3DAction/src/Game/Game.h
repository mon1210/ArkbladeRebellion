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
#include "..\HealCounter\HealCounter.h"
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
class HealCounter;


class Game : public IGameScene
{
public:
	/**
	* @brief Game�̃R���X�g���N�^
	*/
	Game(SceneManager* System_);
	~Game(void);
	/**
	* @brief �Ǘ����\�b�h
	* @note
	* @return GAMESCENE_DEFAULT: �p�� / GAMESCENE_END_FAILURE: �Q�[���I�[�o�[
	*/
	GameSceneResultCode move() override;
	/**
	* @brief �`�揈��
	* @note  ���t���[�����s�����
	*/
	void draw() override;
	// �ȉ��擾�p�萔=================================================== //
	Player			*GetPlayer();			// Player���擾���ĕԂ�
	Enemy			*GetEnemy();			// Enemy���擾���ĕԂ�
	ModelManager	*GetModelManager();		// Model���擾���ĕԂ�
	Camera			*GetCamera();			// Camera���擾���ĕԂ�
	BG				*GetBG();				// BG���擾���ĕԂ�
	Collision		*GetCollision();		// Collision���擾���ĕԂ�
	Radar			*GetRadar();			// Radar���擾���ĕԂ�
	// �ȏ�擾�p�萔=================================================== //
private:
	/**
	* @brief ���������\�b�h
	* @note  �ʃN���X�̏��������\�b�h���Ǘ�
	*/
	void initialize();
	/**
	* @brief �X�V���\�b�h
	* @note  ���t���[���̏���
	*		 �ʃN���X�̍X�V���\�b�h���Ǘ�
	*/
	void update();
private:
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
	HealCounter  *pHealCounter = nullptr;
	StagePhase	 stagePhase = StagePhase::STAGE_INIT;	// ��Ԃ�\��
	int			 timer = 0;
	int			 startTime = 0;							// FadeOut�J�n���Ԏ擾�p
	bool		 bPause = false;						// �|�[�Y�{�^���A�Ŗh�~�t���O
	bool		 isFadeStart = false;					// FadeOut���J�n�������ǂ�����flag
};

//	�}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }