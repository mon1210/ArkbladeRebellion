/**
* @file SceneManager.cpp
* @brief �N���XSceneManager�̎����t�@�C��
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
#include "Game.h"


/**
* @brief SceneManager�̃R���X�g���N�^
*/
SceneManager::SceneManager()
{
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
	GameSceneResultCode Rc = GAMESCENE_DEFAULT;

	switch (GamePhase) {

	case GAMEPHASE_INIT:
		GamePhase = GAMEPHASE_RESET;

	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		GamePhase = GAMEPHASE_TITLE;
		
	// �^�C�g���V�[��
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			Rc = pScene->move();
		if (Rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Game(this);
		GamePhase = GAMEPHASE_GAME;
		
		// �Q�[���V�[��
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			Rc = pScene->move();
		else // pScene == NULL
		{
			printf("");		// Debug
		}
		if (Rc == GAMESCENE_DEFAULT)
			break;

		GamePhase = GAMEPHASE_RESET;
	}
}


/**
* @brief �S�̂̕`����s���֐�
*/
void SceneManager::doDraw() {

	// 1�o�C�g�̃r�b�g��(2^8)
	TCHAR	Str[256];

	//	�V�[����`��
	if (pScene != NULL)
		pScene->draw();
	else // pScene == NULL
	{
		printf("");		// Debug
	}
}


/**
* @brief �V�[���J�ڎ��̃t�F�[�h�A�E�g�@Todo ������
* @note  Title => Game , Game => Title �Ɏg�p
*/
void SceneManager::fadeOut()
{
	int ElapsedFrames = (GetNowCount() - startTime) * FRAME / 1000;  // �o�߃t���[����	 / 1000 => 60(f/s)������
	fadeTimer = clamp(ElapsedFrames, 0, fadeTime);

	// �t�F�[�h�A�E�g����
	if (fadeTimer < fadeTime)
	{
		int Opacity = MAX_OPACITY * (fadeTimer / fadeTime);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Opacity);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	return;

}