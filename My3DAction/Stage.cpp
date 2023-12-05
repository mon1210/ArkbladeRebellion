// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[���̔w�i���Ǘ�����N���X�Ɗ֘A�f�[�^���`
#include "BG.h"
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "Stage.h"
// �v���C���[�L�����N�^�[�Ƃ��̊֘A�����`�����N���X�ƒ萔/�񋓌^�̒�`
#include "Player.h"
// �G�L�����N�^�[�Z�b�g�A�b�v�ƊǗ��Ɋւ���N���X�ƃf�[�^�̒�`
#include "Enemy.h"
// 
#include "camera.h"
// 
#include "Model.h"
// 
#include "Grid.h"
// 
#include "Collider.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"


/**
* @brief Stage�̃R���X�g���N�^
*/
Stage::Stage(Selector *pSystem)
{
	System = pSystem;
	pModel = NULL;
	pCamera = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;
	pCollider = NULL;

	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;
	tileHandle = 0;

	pModel = new Model();
	pCamera = new Camera();
	pCollider = new Collider();
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pBG = new BG();
	pGrid = new Grid();

	pModel->LoadModel();
	pBG->setTileModel(pModel->GetTileModel());
	pPlayer->setPlayerModel(pModel->GetPlayerModel());
	pEnemy->setEnemyModel(pModel->GetEnemyModel());
	pEnemy->setTileModel(pBG->GetModelHandle());
	pCollider->setTileModel(pBG->GetModelHandle());


}


// �f�X�g���N�^
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
* @note �����̏��Ԃ� �I�u�W�F�N�g�� move ���Ă���e�X collide ������āA�K�v�Ȃ�e���W�𒲐�����
* @return GAMESCENE_DEFAULT: �p�� / GAMESCENE_END_FAILURE: �Q�[���I�[�o�[
*/
GameSceneResultCode Stage::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
		// Tile�ɓ����蔻��t�^
		tileHandle = pBG->GetModelHandle();
		MV1SetupCollInfo(
			tileHandle = 0,		// �����蔻���ݒ肷�郂�f���̃n���h��
			-1,					// �ΏۂƂȂ郂�f���̃t���[���ԍ�(-1�͑S��)	
			32,					// X���̋�ԕ�����
			32,					// Y���̋�ԕ�����
			32					// Z���̋�ԕ�����
		);
		pEnemy->InitAnimation();
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
* @note  ���݂̃}�b�v�Ǝ��̃}�b�v�𓮂����Ȃ���`�悷�邱�Ƃňړ����Ă���悤�Ɍ�����
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
				pCamera->SetCameraPositionAndDirection(pPlayer->GetPlayerPos());
				pPlayer->setPlayerNewPos(pCamera->MoveAlongHAngle(pPlayer->GetPlayerMoveVec(), pPlayer->GetPlayerPos()));
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

Collider *Stage::GetCollider()
{
	return pCollider;
}
