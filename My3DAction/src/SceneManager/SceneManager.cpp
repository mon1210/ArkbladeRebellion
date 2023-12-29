/**
* @file SceneManager.cpp
* @brief �N���XSceneManager�̎����t�@�C��
*/
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
* @brief �S�̂̃A�j���[�g���s���֐�
*
*/
void SceneManager::doAnim() {
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
* @brief �S�̂̕`����s���֐�
*/
void SceneManager::doDraw() {

	// 1�o�C�g�̃r�b�g��(2^8)
	TCHAR	Str[256];

	//	�V�[����`��
	if (pScene != nullptr)
		pScene->draw();
}


/**
* @brief �V�[���J�ڎ��̃t�F�[�h�A�E�g�@Todo ������
* @note  Title => Game , Game => Title �Ɏg�p
*/
void SceneManager::fadeOut()
{
	int c = 0;

	//while (1)
	//{
	//	if (c >= 0 && c < 256)                    �@//c��0�`256�̎�
	//		SetDrawBright(c, c, c);					//�i�X�����邭(c= 0->255)
	//	if (c >= 256 && c < 400)                  �@//c��256�`400�̎�
	//		SetDrawBright(255, 255, 255);			//�ʏ�̖��邳
	//	if (c >= 400 && c < 400 + 256)              //c��400�`400+256�̎�
	//		SetDrawBright(255 - (c - 400), 255 - (c - 400), 255 - (c - 400));	//�i�X�Â�(c = 255 -> 0)

	//	DrawBox(0, 0, 640, 480, WHITE, TRUE);		//��ʑS�̂ɔ����l�p�`��`��

	//	c++;										//c���J�E���g�A�b�v

	//	if (c == 400 + 256) break;                  //�Â��Ȃ�I�������I��
	//}


}