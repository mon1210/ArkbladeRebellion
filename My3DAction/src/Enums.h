/*
* @file		Enums.h
* @brief	eunm�ϐ��錾�p�w�b�_�t�@�C��
* @note		�N���X���Ɣ�邽��namespace�ɂ̓v���t�B�N�X�t�^
*/
#pragma once

// �Q�[���̏�Ԃ�\��
enum class GamePhase 
{
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200
};

// �V�[���̏�Ԃ��Ǘ�
enum class GameSceneResultCode 
{
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

// �^�C�g���̏�Ԃ�\��
enum class TitlePhase 
{
	TITLE_INIT = 0,
	TITLE_RUN = 1,
	TITLE_FADE = 2,
	TITLE_DONE = 3
};

// �X�e�[�W�̏�Ԃ�\��
enum class StagePhase 
{
	STAGE_INIT = 0,
	STAGE_RUN = 1,
	STAGE_PAUSE = 2,
	STAGE_FADE = 3,
	STAGE_DONE = 4,
};

// ���f���̎��
enum class ModelType
{
	Default = -1,			// -1����p
	Player,
	PlayerWithSword,	// ������������v���C���[
	Enemy,
	Tile				// ��

};

// �v���C���[���f���̃A�j���[�V�����ԍ�
namespace ePlayer
{
	enum class AnimationNum
	{
		Default = -1,	// -1����p
		Idle = 1,
		Run,
		NoMoveRoll,		// ���̏��
		Roll,
		SpeedRoll,		// �f����
		Damage = 9,
		Drinking,		// ��
		Dying, 
	};
}

// ������������v���C���[���f���̃A�j���[�V�����ԍ�
namespace ePlayerWS
{
	enum class AnimationNum
	{
		Default = -1,	// -1����p
		Idle = 0,
		Slash1,			// �U�� ��i��
		Slash2,			// ��i��
		Slash3,			// �O�i��
	};
}

// �G�l�~�[���f���̃A�j���[�V�����ԍ�
namespace eEnemy
{
	enum class AnimationNum
	{
		Default = -1,	// -1����p
		Idle = 1,
		Run,
		Swiping,		// �U��
		Damage,
		Dying
	};
}

// �v���C���[�̏�Ԃ�\��
enum class PlayerState
{
	Default = -1,		// -1����p
	Idle,
	Move,
	Roll,
	Attack,
	Damage,
	Healing,
	Death

};

// �G�l�~�[�̏�Ԃ�\��
enum class EnemyState
{
	Default = -1,	// -1����p
	Wait,
	Move, 
	Chase,
	Attack,
	Damage,
	Death,

};

// Radar�ɉf��Point�̎��
namespace eRadar
{
	enum class PointType
	{
		Default = -1,	// -1����p
		Enemy,
	};
}
