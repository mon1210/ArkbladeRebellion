// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// Direct2D�̃w�b�_�t�@�C�����C���N���[�h
#include <d2d1.h>
//�o�������X�g (Doubly Linked List) �f�[�^�\�����
#include <list>
// �Q�[���̔w�i���Ǘ�����N���X�Ɗ֘A�f�[�^���`
#include "BG.h"
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "Stage.h"
// �e�N�X�`���ƃr�b�g�}�b�v�̓ǂݍ��݂ƊǗ��Ɋւ���N���X�ƃC���^�[�t�F�[�X���`
#include "TextureLoader.h"
// �v���C���[�L�����N�^�[�Ƃ��̊֘A�����`�����N���X�ƒ萔/�񋓌^�̒�`
#include "Player.h"
// �G�L�����N�^�[�Z�b�g�A�b�v�ƊǗ��Ɋւ���N���X�ƃf�[�^�̒�`
#include "Enemy.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"


/**
* @brief Shot�̃R���X�g���N�^
*/
Stage::Stage(Selector* pSystem)
{
	ID3D11RenderTargetView* pTarget = NULL;
	ID2D1RenderTarget* pTarget2D = NULL;
	System = pSystem;
	pPlayer = NULL;
	pEnemy = NULL;
	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;

	pTarget = System->GetRenderTarget();
	if (pTarget)
	{
		pPlayer = new Player(this);
		pEnemy = new Enemy(this);

	}
	pTarget2D = System->GetRenderTarget2D();
	if(pTarget2D)
	{
		pBG = new BG(pTarget2D);

	}

	SAFE_RELEASE(pTarget);
	SAFE_RELEASE(pTarget2D);


}


// �f�X�g���N�^
Stage::~Stage()
{

	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pBG);

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
void Stage::draw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget)
{
	switch (Phase)
	{
	/* case STAGE_MAPCHANGE_X:
			break;
	   case STAGE_MAPCHANGE_Y:
			break;
	*/
		default:
			if (pBG)
				pBG->draw(pRenderTarget);
			if (pPlayer)
				pPlayer->Update();
			if (pEnemy)
				pEnemy->Update();
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		//float opacity = (float)Timer / STAGE_DONE_TIMER;

		//D2D1_SIZE_F size;
		//size = pRenderTarget->GetSize();

		//D2D1_RECT_F		rc;		// �`��̈�(��ʏ�ł̈ʒu��T�C�Y)���w�肷��ϐ�
		//rc.left = 0;	// �`��̈�̍�����w��
		//rc.top = 0;	//			�V
		//rc.right = size.width;		// �`��̈�̉E�����w��
		//rc.bottom = size.height;		//			�V
		//m_pBlackBrush->SetOpacity(opacity);
		//pRenderTarget->FillRectangle(rc, m_pBlackBrush);
	}
		break;
	default:
		break;
	}

}