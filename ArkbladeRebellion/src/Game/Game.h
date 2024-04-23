/**
* @file		Game.h
* @brief	�N���X Game �̐錾
*/
#pragma once
#include "..\SceneManager\SceneManager.h"
#include "..\BG\BG.h"
#include "..\Player\Player.h"
#include "..\Enemy\Enemy.h"
#include "..\Enums.h"
#include "..\Camera\Camera.h"
#include "..\DrawDebugKey\DrawDebugKey.h"
#include "..\ModelManager\ModelManager.h"
#include "..\Collision\Collision.h"
#include "..\Radar\Radar.h"
#include "..\HPBar\HPBar.h"
#include "..\HealCounter\HealCounter.h"
#include "..\Constants.h"

//! �N���X�̑O���錾
class SceneManager;
class Player;
class Enemy;
class ModelManager;
class Camera;
class DrawDebugKey;
class BG;
class Collision;
class Radar;
class HPBar;
class HealCounter;


class Game : public IGameScene
{
public:
	/**
	* @brief Game�̃R���X�g���N�^
	*/
	Game(SceneManager *System);

	/**
	* @brief Game�̃f�X�g���N�^
	*/
	~Game();

	/**
	* @brief �Ǘ����\�b�h
	* @note
	* @return GAMESCENE_DEFAULT: �p�� / GAMESCENE_END_FAILURE: �Q�[���I�[�o�[
	*/
	GameSceneResultCode move() override;
	/**
	* @brief �`�揈��
	* @note  ���t���[�����s�����
	*/
	void draw() override;

	// �ȉ��擾�p�萔=================================================== //
	/**
	* @brief Player���擾���ĕԂ�
	*/
	Player *GetPlayer();

	/**
	* @brief Enemy���擾���ĕԂ�
	*/
	Enemy *GetEnemy();

	/**
	* @brief Model���擾���ĕԂ�
	*/
	ModelManager *GetModelManager();

	/**
	* @brief Camera���擾���ĕԂ�
	*/
	Camera *GetCamera();

	/**
	* @brief BG�̃��f�����擾���ĕԂ�
	*/
	int GetBGModel();

	/**
	* @brief Collision���擾���ĕԂ�
	*/
	Collision *GetCollision();

	/**
	* @brief Radar���擾���ĕԂ�
	*/
	Radar *GetRadar();
	// �ȏ�擾�p�萔=================================================== //
private:
	/**
	* @brief ���������\�b�h
	* @note  �ʃN���X�̏��������\�b�h���Ǘ�
	*/
	void initialize();

	/**
	* @brief �X�V���\�b�h
	* @note  ���t���[���̏���
	*		 �ʃN���X�̍X�V���\�b�h���Ǘ�
	*/
	void update();
private:
	SceneManager *pSystem = nullptr;
	Player		 *pPlayer = nullptr;
	Enemy		 *pEnemy = nullptr;
	ModelManager *pModelManager = nullptr;
	Camera		 *pCamera = nullptr;
	DrawDebugKey *pDrawDebugKey = nullptr;
	BG			 *pBG = nullptr;
	Collision	 *pCollision = nullptr;
	Radar		 *pRadar = nullptr;
	HPBar		 *pHPBar = nullptr;
	HealCounter  *pHealCounter = nullptr;
	//! ��Ԃ�\��
	StagePhase	 stagePhase = StagePhase::STAGE_INIT;
	int			 timer = 0;
	//! FadeOut�J�n���Ԏ擾�p
	int			 startTime = 0;
	//! FadeOut���J�n�������ǂ�����flag
	bool		 isFadeStart = false;
};

//	�ȉ� �}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
/**
* @def SAFE_RELEASE
* @brief �|�C���^�̉��
*/
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
/**
* @def SAFE_DELETE
* @brief �|�C���^�̍폜
*/
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
/**
* @def SAFE_DELETE_ARRAY
* @brief �|�C���^�z��̍폜
*/
#define SAFE_DELETE_ARRAY(o) if(o){ delete [] (o); o = NULL; }