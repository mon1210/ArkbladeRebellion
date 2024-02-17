// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "..\stdafx.h"
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "SceneManager.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "..\Constants.h"
// �^�C�g����ʂ̃Q�[���V�[�����Ǘ�����w�b�_�t�@�C��
#include "..\Title\Title.h"
// �Q�[�����̃X�e�[�W�֘A�N���X�Ɨ񋓌^�̒�`
#include "..\Game\Game.h"


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
* @brief �Q�[���S�̂̃V�[����Phase���Ǘ�
*/
void SceneManager::manageSceneAndPhase() {
	GameSceneResultCode Rc = GameSceneResultCode::GAMESCENE_DEFAULT;

	switch (GamePhase) {

	case GamePhase::GAMEPHASE_INIT:
		GamePhase = GamePhase::GAMEPHASE_RESET;

	case GamePhase::GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		GamePhase = GamePhase::GAMEPHASE_TITLE;
		
	// �^�C�g���V�[��
	case GamePhase::GAMEPHASE_TITLE:
		if (pScene != nullptr)
			Rc = pScene->move();
		if (Rc == GameSceneResultCode::GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Game(this);
		GamePhase = GamePhase::GAMEPHASE_GAME;
		
		// �Q�[���V�[��
	case GamePhase::GAMEPHASE_GAME:
		if (pScene != nullptr)
			Rc = pScene->move();
		if (Rc == GameSceneResultCode::GAMESCENE_DEFAULT)
			break;

		GamePhase = GamePhase::GAMEPHASE_RESET;
	}
}


/**
* @brief �Q�[���S�̂̕`����s���֐�
*/
void SceneManager::doDraw() {

	//	�V�[����`��
	if (pScene != nullptr)
		pScene->draw();
}


/**
* @brief �V�[���J�ڎ��̃t�F�[�h�A�E�g
* @note  Title => Game , Game => Title �Ɏg�p
*/
void SceneManager::fadeOut(int start_time)
{
	// startTime�̓t�F�[�h�A�E�g���n�܂鎞�ԂŎ擾
	float elapsedFrames = (GetNowCount() - start_time) * (FRAME / 1) / 1000;  // �o�߃t���[����	 / 1000 => 60(f/s)������
	fadeTimer = clampF(elapsedFrames, 0.f, fadeTime);

	// �t�F�[�h�A�E�g����
	if (fadeTimer < fadeTime)
	{
		// (fadeTimer / fadeTime) �������邩�Ŏ��s
		float opacity = MAX_OPACITY * (fadeTimer / fadeTime);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(opacity));
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}