// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "..\stdafx.h"
#include "Game.h"


// �R���X�g���N�^
Game::Game(SceneManager *System)
{
	pSystem = System;

	// �C���X�^���X��
	pModelManager = new ModelManager();
	pCamera = new Camera(this);
	pBG = new BG(this);
	pDrawDebugKey = new DrawDebugKey();
	pCollision = new Collision(this);	// �K��Player����ɏ���
	pRadar = new Radar();				// �K��Player����ɏ���
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pHPBar = new HPBar(this);
	pHealCounter = new HealCounter(this);
}


// ���������\�b�h
void Game::initialize()
{
	if (pPlayer)
		pPlayer->initialize(MAX_HP);
	if (pEnemy)
		pEnemy->initialize(ENEMY_MAX_HP);
	if (pCollision && pBG)
		pCollision->initialize(pBG->GetModelHandle());

}


// �X�V���\�b�h
void Game::update()
{
	if (pPlayer)
		pPlayer->update();
	if (pCamera)
		pCamera->update();
	if (pEnemy)
		pEnemy->update();
	if (pHPBar)
		pHPBar->update();
	if (pHealCounter)
		pHealCounter->update();
}


// �f�X�g���N�^
Game::~Game()
{
	SAFE_DELETE(pCollision);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pDrawDebugKey);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModelManager);
	SAFE_DELETE(pRadar);
	SAFE_DELETE(pHPBar);
	SAFE_DELETE(pHealCounter);
}


// �Ǘ����\�b�h
GameSceneResultCode Game::move()
{
	switch (stagePhase)
	{
	case StagePhase::STAGE_INIT:
		initialize();
		stagePhase = StagePhase::STAGE_RUN;
		break;

	case StagePhase::STAGE_RUN:
		// --------------------- STAGE_RUN START ------------------- //

		//	�|�[�Y��ʌĂяo��
		if (CheckHitKey(KEY_INPUT_P))		// P 
		{
			if (!bPause) 
			{
				stagePhase = StagePhase::STAGE_PAUSE;
				bPause = true;
			}
		}
		else 
		{
			bPause = false;
		}

		if (pPlayer && pEnemy)
		{
			if (!pPlayer->isAlive() || !pEnemy->isAlive())
			{
				stagePhase = StagePhase::STAGE_FADE;
				timer = 0;
			}
			if (pRadar)
				pRadar->listReset();	// Point���X�g������
			
			// �X�V
			update();		
		}
		break;
		// --------------------- STAGE_RUN END --------------------- //

	case StagePhase::STAGE_PAUSE:
		//	�|�[�Y��ʌĂяo��
		if (GetAsyncKeyState(KEY_INPUT_P))	
		{
			if (!bPause) 
			{
				stagePhase = StagePhase::STAGE_RUN;
				bPause = true;
			}
		}
		else 
		{
			bPause = false;
		}

		break;

	case StagePhase::STAGE_FADE:
		if (timer++ >= STAGE_FADE_TIMER)
		{
			stagePhase = StagePhase::STAGE_DONE;
		}
		break;

	case StagePhase::STAGE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;

	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


// �`�揈��
void Game::draw()
{
	if (pBG)
		pBG->draw();
	if (pDrawDebugKey)
		pDrawDebugKey->draw();
	if (pPlayer)
		pPlayer->draw();
	if (pEnemy)
		pEnemy->draw();
	if (pRadar)
		pRadar->draw();
	if (pHPBar)
		pHPBar->draw();
	if (pHealCounter)
		pHealCounter->draw();

	// �t�F�[�h�A�E�g�`��p
	switch (stagePhase)
	{
	case StagePhase::STAGE_FADE:
	case StagePhase::STAGE_DONE:
		// �t�F�[�h�A�E�g����
		if (!isFadeStart)
		{
			startTime = GetNowCount();
			isFadeStart = true;
		}
		pSystem->fadeOut(startTime);
		break;
	}
}


// ModelManager���擾���ĕԂ�
ModelManager *Game::GetModelManager()
{
	return pModelManager;
}


// Collision���擾���ĕԂ�
Collision *Game::GetCollision()
{
	return pCollision;
}


// Radar���擾���ĕԂ�
Radar *Game::GetRadar()
{
	return pRadar;
}


// BG�̃��f�����擾���ĕԂ�
int Game::GetBGModel()
{
	if (pBG)
		return pBG->GetModelHandle();
	else
		return -1;
}


// Player���擾���ĕԂ�
Player *Game::GetPlayer()
{
	return pPlayer;
}


// Camera���擾���ĕԂ�
Camera *Game::GetCamera()
{
	return pCamera;
}


// Enemy���擾���ĕԂ�
Enemy *Game::GetEnemy() 
{
	return pEnemy;
}