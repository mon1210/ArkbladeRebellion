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
	float	GetHp() { return hitPoint; }

	/**
	* @brief �U���q�b�g����t���O���擾���ĕԂ�
	*/
	bool GetIsHitFlag() { return isAttackHit; }
	// �ȏ�擾�p�萔===================================================================== //
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
	//! �A�j���[�V�����̑��Đ�����
	float* animTimes = 0;
	//! �A�j���[�V�����̌��݂̍Đ�����
	float	animTimer = 0.f;
	//! ����		�A�^�b�`����rad�ɕϊ�
	float	angle = 0.f;
	//! HP
	float	hitPoint = 100.f;
	//! HP���ω��������𔻒f����p�̕ϐ�
	float	currentHP = 0.f;
	//! ���S�t���O
	bool	isDeath = false;
	//! ���g�̍U���������������̃t���O
	bool	isAttackHit = false;

	//!  �֐��|�C���^�̌^���`
	typedef std::function<void()> stateFunction;
};