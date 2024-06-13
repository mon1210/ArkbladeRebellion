/**
* @file		Player.h
* @brief	�N���X Player �̐錾
*/
#pragma once
#include "..\CharaBase\CharaBase.h"

#include "..\Animation\Animation.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\Game\Game.h"
#include "..\GlobalFunctions\GlobalFunctions.h"
#include "..\OBBCollider\OBBCollider.h"

//! �N���X�̑O���錾
class CharaBase;
class Game;
class OBBCollider;

class Player : public CharaBase
{
public:
	/**
	* @brief Player�̃R���X�g���N�^
	*/
	Player(Game *Game);

	/**
	* @brief Player�̃f�X�g���N�^
	*/
	~Player() override;

	/**
	* @brief  �������ɂ����ʂƂ��ĕԂ�
	* @return true:���� / false:���S
	*/
	bool isAlive() override;

	/**
	* @brief �`�惁�\�b�h
	*/
	void draw() override;

	/**
	* @brief ���������\�b�h
	* @note  �g�������l����������HP���w��
	* @param[in] hit_point  �L������HP
	*/
	void initialize(int hit_point) override;

	/**
	* @brief �s����Ԃ̊Ǘ����\�b�h
	* @note  ���t���[���̏���
	*/
	void update() override;

	// �ȉ��擾�p�萔====================================================================== //
	/**
	* @brief healCount���擾���ĕԂ�
	*/
	int		GetHealCount();

	/**
	* @brief mOBBCol���擾���ĕԂ�
	*/
	OBBCollider GetOBBCol();
	// �ȏ�擾�p�萔====================================================================== //
private:
	/**
	* @brief unordered_map���������\�b�h
	* @note  �eState���Ƃ̃��\�b�h��o�^
	*/
	void initializeStateFunctions() override;

	/**
	* @brief �@�ړ��L�[�`�F�b�N
	* @details ���������Ȍ���
	*/
	bool checkMoveKey();

	/**
	* @brief �@��]�L�[�`�F�b�N
	* @details ���������Ȍ���
	*/
	bool checkRollKey();

	/**
	* @brief Roll�̃N�[���_�E���Ǘ����\�b�h
	* @note  �N�[���^�C�������炵�A0�ɂȂ��Roll���ł���悤��
	*/
	void manageRollCooldown();

	/**
	* @brief Attack����Idle�ɖ߂�ۂ̏������\�b�h
	*/
	void changeAttackToIdle();

	/**
	* @brief �ړ���̍��W��ݒ肷��
	* @note  �ړ����ɌĂяo��
	*/
	void moveHandle() override;

	/**
	* @brief �ړ����̍s���Ǘ�
	* @note  �A�j���[�V�����ƌ����̐ݒ������
	*        moveFlag�͂�����true��
	* @param[in] num�@	        �A�j���[�V�����ԍ�
	* @param[in] rotate_angle�@	��]�p�x
	* @param[in] move_x�@	    x�������̈ړ��X�s�[�h
	* @param[in] move_z�@	    z�������̈ړ��X�s�[�h
	*/
	void animateAndMove(ePlayer::AnimationNum num, float rotate_angle, float move_x, float move_z);
private:
	// �ȉ� ��Ԃ��Ƃ̃��\�b�h ---------------------
	/**
	* @brief �ҋ@��Ԃ̊Ǘ����\�b�h
	*/
	void idle();

	/**
	* @brief �ړ���Ԃ̊Ǘ����\�b�h
	*/
	void move();

	/**
	* @brief ��]��Ԃ̊Ǘ����\�b�h
	*/
	void roll();

	/**
	* @brief �U����Ԃ̊Ǘ����\�b�h
	*/
	void attack();

	/**
	* @brief ��_���[�W��Ԃ̊Ǘ����\�b�h
	*/
	void damage();

	/**
	* @brief �񕜏�Ԃ̊Ǘ����\�b�h
	*/
	void healing();

	/**
	* @brief ���S��Ԃ̊Ǘ����\�b�h
	*/
	void death();
	// �ȏ� ��Ԃ��Ƃ̃��\�b�h ---------------------
private:
	//! �̗p OBBCollider�C���X�^���X��   ��_���[�W���g�p
	OBBCollider mOBBCol = OBBCollider(PLAYER_OBB_SCALE, PLAYER_OBB_ANGLE, PLAYER_OBB_TRANS);

	//! ���p OBBCollider�C���X�^���X��   �U�����g�p
	OBBCollider mOBBColSword = OBBCollider(SWORD_OBB_SCALE, SWORD_OBB_ANGLE, SWORD_OBB_TRANS);
private:
	Game	*pGame = nullptr;
	//! �񕜉\��
	int		healCount = 0;
	//! ��]�̃N�[���^�C���Ǘ��ϐ�
	float	rollCoolTime = 0.f;
	//! ��������������f���̃A�j���[�V�������Đ�����
	float	*withSwordAnimTimes = 0;
	//! Roll�\�t���O
	bool	rollAble = true;
	//! ��]���t���O
	bool	isRoll = false;
	//! �U���A�j���[�V�������Z�b�g����Ă��邩�̃t���O
	bool	isAttackAnim = false;
	//! ��i�ڂ̍U�����ǂ����̃t���O
	bool	isFirst = false;
	//! ��i�ڂ̍U�����ǂ����̃t���O
	bool	isSecond = false;
	//! �O�i�ڂ̍U�����ǂ����̃t���O
	bool	isThird = false;
	
	//! ��Ԃ�\��
	PlayerState currentState = PlayerState::Idle;

	//! �֐��̓�����unordered_map���`
	std::unordered_map<PlayerState, stateFunction> stateFunctionMap;
};


//	�ȉ� �}�N����`
/**
* @def Key_ForwardMove
* @brief �O�i�L�[�̓��͂𔻒�
*/
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_W)
/**
* @def Key_BackMove
* @brief ��ރL�[�̓��͂𔻒�
*/
#define Key_BackMove		CheckHitKey(KEY_INPUT_S)
/**
* @def Key_RightMove
* @brief �E�ړ��L�[�̓��͂𔻒�
*/
#define Key_RightMove		CheckHitKey(KEY_INPUT_D)
/**
* @def Key_Left_Move
* @brief ���ړ��L�[�̓��͂𔻒�
*/
#define Key_Left_Move		CheckHitKey(KEY_INPUT_A)

/**
* @def Key_ForwardRoll
* @brief �O�]�L�[�̓��͂𔻒�
*/
#define Key_ForwardRoll		CheckHitKey(KEY_INPUT_UP)
/**
* @def Key_RightRoll
* @brief �E��]�L�[�̓��͂𔻒�
*/
#define Key_RightRoll		CheckHitKey(KEY_INPUT_RIGHT)
/**
* @def Key_LeftRoll
* @brief ����]�L�[�̓��͂𔻒�
*/
#define Key_LeftRoll		CheckHitKey(KEY_INPUT_LEFT)
/**
* @def Key_BackRoll
* @brief ����]�L�[�̓��͂𔻒�
*/
#define Key_BackRoll		CheckHitKey(KEY_INPUT_DOWN)

/**
* @def Key_Attack
* @brief �U���L�[�̓��͂𔻒�
*/
#define Key_Attack			CheckHitKey(KEY_INPUT_V)
/**
* @def Key_Healing
* @brief �񕜃L�[�̓��͂𔻒�
*/
#define Key_Healing			CheckHitKey(KEY_INPUT_C)