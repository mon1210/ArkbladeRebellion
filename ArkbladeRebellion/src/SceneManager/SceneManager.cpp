#include "SceneManager.h"


// �R���X�g���N�^
SceneManager::SceneManager()
{
	startTime = GetNowCount();
}


// �f�X�g���N�^
SceneManager::~SceneManager()
{
	SAFE_DELETE(pScene);
}


// �Q�[���S�̂̃V�[����Phase���Ǘ�
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


// �Q�[���S�̂̕`����s��
void SceneManager::doDraw() {

	//	�V�[����`��
	if (pScene != nullptr)
		pScene->draw();
}


/*
	�V�[���J�ڎ��̃t�F�[�h�A�E�g
	Title => Game , Game => Title �Ŏg�p
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