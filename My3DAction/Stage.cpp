// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "Stage.h"


/**
* @brief Stage�̃R���X�g���N�^
*/
Stage::Stage()
{
	pModel = NULL;
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
	tileHandle = 0;

	// �C���X�^���X��
	pModel = new Model();
	pCamera = new Camera();
	pCollision = new Collision();	// �K��Player����ɏ���
	pRadar = new Radar();		// �K��Player����ɏ���
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pBG = new BG();
	pGrid = new Grid();

	// ���f���Z�b�g
	pModel->loadModel();
	pBG->setTileModel(pModel->getTileModel());
	pPlayer->setPlayerModel(pModel->getPlayerModel());
	pEnemy->setEnemyModel(pModel->getEnemyModel());
	pEnemy->setTileModel(pBG->getModelHandle());
	pCollision->setTileModel(pBG->getModelHandle());
	tileHandle = pBG->getModelHandle();
}


/**
* @brief �f�X�g���N�^
* @note	 ���ׂẴ|�C���^��������Delete
*/
Stage::~Stage()
{
	SAFE_DELETE(pCollision);
	SAFE_DELETE(pGrid);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModel);
	SAFE_DELETE(pRadar);
}


/**
* @brief �A�j���[�V����(1�t���[��)�̎��s
* @note 
* @return GAMESCENE_DEFAULT: �p�� / GAMESCENE_END_FAILURE: �Q�[���I�[�o�[
*/
GameSceneResultCode Stage::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
		pCollision->initCollision(tileHandle);
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
void Stage::draw()
{
	switch (Phase)
	{
		default:
			if (pRadar)
				pRadar->listReset();	// Point���X�g������
			if (pBG)
				pBG->draw();
			if (pGrid)
				pGrid->draw();
			if (pPlayer)
				pPlayer->draw();
			if (pCamera) {
				pCamera->controller();
				pCamera->setPositionAndDirection(pPlayer->getPlayerPos());			//�J�����̈ʒu�E�p�x�ݒ� 
				if (pPlayer) {
					pPlayer->setCameraHAngle(pCamera->getHorizontalAngle());		// �J�����̐����p�x�擾
					pPlayer->setPlayerNewPos(pCamera->moveAlongHAngle
						(pPlayer->getPlayerMoveVec(), pPlayer->getPlayerPos()));	// �v���C���[�̍��W�ݒ�
				}
			}			
			if (pEnemy) {
				pEnemy->update();
				pEnemy->setPlayerPos(pPlayer->getPlayerPos());
			}
			if (pRadar)
				pRadar->draw();
				
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		// �t�F�[�h�A�E�g����
	}
		break;
	default:
		break;
	}

}


/**
* @brief Collision���擾���ĕԂ�
*/
Collision *Stage::GetCollision()
{
	return pCollision;
}


/**
* @brief Radar���擾���ĕԂ�
*/
Radar* Stage::GetRadar()
{
	return pRadar;
}