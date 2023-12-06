// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "Stage.h"


/**
* @brief Stage�̃R���X�g���N�^
*/
Stage::Stage(Selector *pSystem)
{
	System = pSystem;
	pModel = NULL;
	pCamera = NULL;
	pCollider = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;

	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;
	tileHandle = 0;

	// �C���X�^���X��
	pModel = new Model();
	pCamera = new Camera();
	pCollider = new Collider();	// �K��Player����ɏ���
	pPlayer = new Player(this);
	pEnemy = new Enemy();
	pBG = new BG();
	pGrid = new Grid();

	// ���f���Z�b�g
	pModel->LoadModel();
	pBG->setTileModel(pModel->GetTileModel());
	pPlayer->setPlayerModel(pModel->GetPlayerModel());
	pEnemy->setEnemyModel(pModel->GetEnemyModel());
	pEnemy->setTileModel(pBG->GetModelHandle());
	pCollider->setTileModel(pBG->GetModelHandle());
	tileHandle = pBG->GetModelHandle();
}


/**
* @brief �f�X�g���N�^
* @note	 ���ׂẴ|�C���^��������Delete
*/
Stage::~Stage()
{
	SAFE_DELETE(pCollider);
	SAFE_DELETE(pGrid);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModel);
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
		pCollider->InitCollision(tileHandle);
		pEnemy->InitAnimation();	// phase������Enemy�݂̂Ȃ̂�
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
			if (pBG)
				pBG->draw();
			if (pGrid)
				pGrid->Draw();
			if (pPlayer)
				pPlayer->draw();
			if (pCamera) {
				pCamera->CameraController();
				pCamera->SetCameraPositionAndDirection(pPlayer->GetPlayerPos());	//�J�����̈ʒu�E�p�x�ݒ� 
				if (pPlayer) {
					pPlayer->setCameraHAngle(pCamera->GetCameraHorizontalAngle());	// �J�����̐����p�x�擾
					pPlayer->setPlayerNewPos(pCamera->MoveAlongHAngle
						(pPlayer->GetPlayerMoveVec(), pPlayer->GetPlayerPos()));	// �v���C���[�̍��W�ݒ�
				}
			}			
			if (pEnemy) {
				pEnemy->Update();
				pEnemy->setPlayerPos(pPlayer->GetPlayerPos());
			}
				
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
* @brief Collider���擾���ĕԂ�
*/
Collider *Stage::GetCollider()
{
	return pCollider;
}
