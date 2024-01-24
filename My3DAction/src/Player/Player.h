/*
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

// �N���X�̑O���錾
class CharaBase;
class Game;
class OBBCollider;

class Player : public CharaBase
{
public:
	/**
	* @brief Player�̃R���X�g���N�^
	*/
	Player(Game *Game_);

	// �f�X�g���N�^
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
	* @param[in] hit_point�@�L������HP�@�g��������̂���
	*/
	void initialize(int hit_point) override;

	/**
	* @brief �s����Ԃ̊Ǘ����\�b�h
	* @note  ���t���[���̏���
	*/
	void update() override;

	// �ȉ��擾�p�萔====================================================================== //
	/**
	* @brief Hp���擾���ĕԂ�
	*/
	float	GetHp();

	/**
	* @brief healCount���擾���ĕԂ�
	*/
	int		GetHealCount();
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
	* @brief ���W�Ɠ����蔻���ݒ肷�郁�\�b�h
	* @note  �ړ����ɌĂяo��
	*/
	void updateMoveAndCollision() override;

	/**
	* @brief �ړ����̍s���Ǘ�
	* @note  �A�j���[�V�����ƌ����̐ݒ������
	*        moveFlag�͂�����true��
	* @param[in] num�@	        �A�j���[�V�����ԍ�
	* @param[in] ROTATE_ANGLE�@	��]�p�x
	* @param[in] move_x�@	    x�������̈ړ��X�s�[�h
	* @param[in] move_z�@	    z�������̈ړ��X�s�[�h
	*/
	void animateAndMove(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z);
private:
	// ��Ԃ��Ƃ̃��\�b�h
	void idle();	// �ҋ@
	void move();	// �ړ�
	void roll();	// ��]
	void attack();	// �U�� => �O�i�U���̗\��
	void damage();	// ��_���[�W
	void healing();	// ��
	void death();	// ���S
private:
	Game		*pGame = nullptr;
	OBBCollider *pOBBCol = nullptr;
	OBBCollider *pOBBColSword = nullptr;
	int		rollCoolTime = 0;
	int		healCount = 0;												// �񕜉\��
	//int		count = 0;
	float	*withSwordAnimTimes = 0;									// ��������������f���̃A�j���[�V�������Đ�����
	bool	rollAble = true;											// Roll�\�t���O
	bool	isRoll = false;												// ��]���t���O
	bool	isAttackAnim = false;										// �U���A�j���[�V�������Z�b�g����Ă��邩�̃t���O
	bool	isFirst = false;											// ��i�ڂ̍U�����ǂ����̃t���O
	bool	isSecond = false;											// ��i�ڂ̍U�����ǂ����̃t���O
	bool	isThird = false;											// �O�i�ڂ̍U�����ǂ����̃t���O

	PlayerState currentState = PlayerState::Idle;						// ��Ԃ�\��

	std::unordered_map<PlayerState, StateFunction> stateFunctionMap;	// �֐��̓�����unordered_map���`
};


// �}�N����`
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_ForwardRoll		CheckHitKey(KEY_INPUT_W)
#define Key_RightRoll		CheckHitKey(KEY_INPUT_D)
#define Key_LeftRoll		CheckHitKey(KEY_INPUT_A)
#define Key_BackRoll		CheckHitKey(KEY_INPUT_S)
#define Key_Attack			CheckHitKey(KEY_INPUT_V)
#define Key_Healing			CheckHitKey(KEY_INPUT_F)