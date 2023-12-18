// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
#include "Game.h"


/**
* @brief Game�̃R���X�g���N�^
*/
Game::Game(SceneManager* System_)
{
	pSystem = System_;

	// �C���X�^���X��
	pModelManager = new ModelManager();
	pCamera = new Camera(this);
	pCollision = new Collision(this);	// �K��Player����ɏ���
	pRadar = new Radar();				// �K��Player����ɏ���
	pBG = new BG(this);
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pGrid = new Grid();
}


/**
* @brief �f�X�g���N�^
* @note	 ���ׂẴ|�C���^��������Delete
*/
Game::~Game()
{
	SAFE_DELETE(pCollision);
	SAFE_DELETE(pGrid);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModelManager);
	SAFE_DELETE(pRadar);
}


/**
* @brief �A�j���[�V����(1�t���[��)�̎��s
* @note 
* @return GAMESCENE_DEFAULT: �p�� / GAMESCENE_END_FAILURE: �Q�[���I�[�o�[
*/
GameSceneResultCode Game::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
		if (pCollision)
			pCollision->initCollision(pBG->GetModelHandle());
		if (pEnemy)
			pEnemy->initAnimation();	// phase������Enemy�݂̂Ȃ̂�
		Phase = STAGE_RUN;
		break;

	case STAGE_RUN:
		// --------------------- STAGE_RUN START ------------------- //

		//	�|�[�Y��ʌĂяo��
		if (GetAsyncKeyState(0x50))		// P 
		{
			if (!bPause) 
			{
				Phase = STAGE_PAUSE;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		if (pPlayer)
		{
			if (!pPlayer->move())
			{
				Phase = STAGE_FADE;
				Timer = 0;
				break;
			}
			if (pRadar)
				pRadar->listReset();	// Point���X�g������
			pPlayer->update();
			if (pCamera)
				pCamera->update();
			if (pEnemy)
				pEnemy->update();
		}
		break;
		// --------------------- STAGE_RUN END --------------------- //

	case STAGE_PAUSE:
		//	�|�[�Y��ʌĂяo��
		if (GetAsyncKeyState(0x50))		// P
		{
			if (!bPause) 
			{
				Phase = STAGE_RUN;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		break;

	case STAGE_FADE:
		if (Timer++ < STAGE_FADE_TIMER)
		{
			break;
		}
		Phase = STAGE_DONE;
		break;

	case STAGE_DONE:
		return GAMESCENE_END_OK;

	}

	return GAMESCENE_DEFAULT;
}


/**
* @brief �`�揈��
* @note  ���t���[�����s�����
*/
void Game::draw()
{
	if (pBG)
		pBG->draw();
	if (pGrid)
		pGrid->draw();
	if (pPlayer)
		pPlayer->draw();
	if (pEnemy)
		pEnemy->draw();
	if (pRadar)
		pRadar->draw();
	if (pCollision)
		pCollision->debugCapColDraw();	    // �f�o�b�O�p�����蔻��J�v�Z���`��
	//if (m_pUI)
	//	m_pUI->draw(pRenderTarget);

	// �t�F�[�h�A�E�g�`��p
	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		// �t�F�[�h�A�E�g����
		pSystem->fadeOut();
	}
		break;
	default:
		break;
	}

}


/**
* @brief ModelManager���擾���ĕԂ�
*/
ModelManager* Game::GetModelManager()
{
	return pModelManager;
}


/**
* @brief Collision���擾���ĕԂ�
*/
Collision *Game::GetCollision()
{
	return pCollision;
}


/**
* @brief Radar���擾���ĕԂ�
*/
Radar *Game::GetRadar()
{
	return pRadar;
}


/**
* @brief BG���擾���ĕԂ�
*/
BG *Game::GetBG()
{
	return pBG;
}


/**
* @brief Player���擾���ĕԂ�
*/
Player *Game::GetPlayer()
{
	return pPlayer;
}


/**
* @brief Camera���擾���ĕԂ�
*/
Camera *Game::GetCamera()
{
	return pCamera;
}


/**
* @brief Enemy���擾���ĕԂ�
*/
Enemy* Game::GetEnemy() 
{
	return pEnemy;
}