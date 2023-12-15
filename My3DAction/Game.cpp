// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
#include "Game.h"


/**
* @brief Game�̃R���X�g���N�^
*/
Game::Game(SceneManager* pSystem)
{
	System = pSystem;
	pModelManager = NULL;
	pCamera = NULL;
	pCollision = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;
	pRadar = NULL;

	Phase = STAGE_INIT;

	bPause = true;

	Timer = 0;

	// �C���X�^���X��
	pModelManager = new ModelManager();
	pCamera = new Camera();
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
		pCollision->initCollision(pBG->getModelHandle());
		pEnemy->initAnimation();	// phase������Enemy�݂̂Ȃ̂�
		Phase = STAGE_RUN;
		break;

	case STAGE_RUN:
		//	�|�[�Y��ʌĂяo��
		if (GetAsyncKeyState(0x50))		 // P 
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
			pPlayer->update();
			if (pRadar)
				pRadar->listReset();	// Point���X�g������
			if (pCamera) {
				pCamera->controller();
				pCamera->setPositionAndDirection(pPlayer->getPos());			//�J�����̈ʒu�E�p�x�ݒ� 
				pPlayer->setCameraHAngle(pCamera->getHorizontalAngle());		// �J�����̐����p�x�擾
				pPlayer->setPlayerNewPos(pCamera->moveAlongHAngle
				(pPlayer->getPlayerMoveVec(), pPlayer->getPos()));	// �v���C���[�̍��W�ݒ�
			}
			if (pEnemy) {
				pEnemy->update();
				pEnemy->setPlayerPos(pPlayer->getPos());
			}

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
	switch (Phase)
	{
		default:
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
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	// �t�F�[�h�A�E�g�`��p
	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		// �t�F�[�h�A�E�g����
		System->FadeOut();
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
BG* Game::GetBG()
{
	return pBG;
}