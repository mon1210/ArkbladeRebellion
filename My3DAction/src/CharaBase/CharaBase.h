/**
* @file		CharaBase.h
* @brief	�N���X CharaBase �̐錾
* @note		Character�̊��N���X�ŁAPlayer��Enemy���p�����Ă���
*			���N���X�ł́A���ʂ���֐��ƕϐ����܂Ƃ߂Đ錾
*/
#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <functional>

//! ���N���X
class CharaBase 
{
public:
	/**
	* @brief �������z�f�X�g���N�^�̎���
	* @note  �f�X�g���N�^�����͗p�ӂ��Ȃ���΁A�T�u�N���X���f�X�g���N�^���ĂׂȂ�
	*/
	virtual ~CharaBase();

	/**
	* @brief  �������ɂ����ʂƂ��ĕԂ�
	* @return true:���� / false:���S
	*/
	virtual bool isAlive() = 0;

	/**
	* @brief �`�惁�\�b�h
	*/
	virtual void draw() = 0;

	/**
	* @brief ���������\�b�h
	* @note  �g�������l����������HP���w��
	* @param[in] hit_point  �L������HP
	*/
	virtual void initialize(float hit_point) = 0;

	/**
	* @brief �s����Ԃ̊Ǘ����\�b�h
	* @note  ���t���[���̏���
	*/
	virtual void update() = 0;

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief ���W���擾���ĕԂ�
	*/
	VECTOR GetPos() { return position; }

	/**
	* @brief Hp���擾���ĕԂ�
	*/
	int	GetHp() { return hitPoint; }

	/**
	* @brief �U���q�b�g����t���O���擾���ĕԂ�
	*/
	bool GetIsHitFlag() { return isAttackHit; }

	/**
	* @brief ��x�̍U���œ�i�U���ɂȂ�Ȃ��悤�ɂ���t���O���擾���ĕԂ�
	*/
	bool GetDamegeFlag() { return isDamageCooldown; }
	// �ȏ�擾�p�萔===================================================================== //

	/**
	* @brief ��x�̍U���œ�i�U���ɂȂ�Ȃ��悤�ɂ���t���O���Z�b�g����
	* @param[in] is_damage_flag ��x�̍U���œ�i�U���ɂȂ�Ȃ��悤�ɂ���t���O
	*/
	void SetDamegeFlag(bool is_damage_flag) { isDamageCooldown = is_damage_flag; }
protected:
	/**
	* @brief unordered_map���������\�b�h
	* @note  �eState���Ƃ̃��\�b�h��o�^
	*/
	virtual void initializeStateFunctions() = 0;

	/**
	* @brief �ړ���̍��W��ݒ肷��
	* @note  �ړ����ɌĂяo��
	*/
	virtual void moveHandle() = 0;
protected:
	//! ���W
	VECTOR	position = VGet(0.f, 0.f, 0.f);
	//! �ړ��̌����x�N�g��
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);
	//! ���f���n���h��
	int		animHandle = 0;
	//! �A�j���[�V�����ԍ�
	int		animNum = 0;
	//! HP
	int		hitPoint = 100;
	//! �A�j���[�V�����̑��Đ�����
	float  *animTimes = 0;
	//! �A�j���[�V�����̌��݂̍Đ�����
	float	animTimer = 0.f;
	//! ����		�A�^�b�`����rad�ɕϊ�
	float	angle = 0.f;
	//! HP���ω��������𔻒f����p�̕ϐ�
	float	currentHP = 0.f;
	//! ���S�t���O
	bool	isDeath = false;
	//! ���g�̍U���������������̃t���O
	bool	isAttackHit = false;
	//! ��x�̍U���œ�i�U���ɂȂ�Ȃ��悤�ɂ���t���O
	bool	isDamageCooldown = false;

	//!  �֐��|�C���^�̌^���`
	typedef std::function<void()> stateFunction;
};