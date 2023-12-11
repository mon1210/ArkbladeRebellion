/**
* @file Selector.cpp
* @brief �N���XSelector�̎����t�@�C��
*/
// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "SceneManager.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"
// �^�C�g����ʂ̃Q�[���V�[�����Ǘ�����w�b�_�t�@�C��
#include "Title.h"
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "Stage.h"


/**
* @brief SceneManager�̃R���X�g���N�^
*/
SceneManager::SceneManager()
{
	// �����o������
	count = 0;
	//wait = 0;
	eGamePhase = GAMEPHASE_INIT;
	pScene = NULL;

	fadeTimer = 0;
	fadeTime = 60;
	startTime = GetNowCount();
}


// �f�X�g���N�^
SceneManager::~SceneManager()
{
	SAFE_DELETE(pScene);
}


/**
* @brief �S�̂̃A�j���[�g���s���֐�
*
*/
void SceneManager::doAnim() {
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {

	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		eGamePhase = GAMEPHASE_TITLE;	// GAME��Debug
		
	// �^�C�g���V�[��
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Stage(this);
		eGamePhase = GAMEPHASE_GAME;
		
		// �Q�[���V�[��
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			rc = pScene->move();
		else // pScene == NULL
		{
			printf("");		// Debug
		}
		if (rc == GAMESCENE_DEFAULT)
			break;

		eGamePhase = GAMEPHASE_RESET;
	}
	// �f�o�b�O�p�J�E���^
	count++;
}


/**
* @brief �S�̂̕`����s���֐�
*/
void SceneManager::doDraw() {

	// 1�o�C�g�̃r�b�g��(2^8)
	TCHAR	str[256];

	//	�V�[����`��
	if (pScene != NULL)
		pScene->draw();
	else // pScene == NULL
	{
		printf("");		// Debug
	}
}

void SceneManager::FadeOut()
{
	int elapsedFrames = (GetNowCount() - startTime) * 60 / 1000;  // �o�߃t���[����
	fadeTimer = Clamp(elapsedFrames, 0, fadeTime);

	// �t�F�[�h�A�E�g����
	if (fadeTimer < fadeTime)
	{
		int opacity = 255 * (fadeTimer / fadeTime);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	return;

}