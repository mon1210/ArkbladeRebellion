/**
* @file		CharaBase.h
* @brief	�N���XCharaBase�̐錾�t�@�C��
* @note		Character�̊��N���X�ŁAPlayer��Enemy���p�����Ă���
*			���N���X�ł́A���ʂ���֐��ƕϐ����܂Ƃ߂Đ錾
*/
#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <functional>

// ���N���X
class CharaBase 
{
public:
	/**
	* @brief   �������z�f�X�g���N�^�̎���
	* @details �f�X�g���N�^�����͗p�ӂ��Ȃ���΁A�T�u�N���X���f�X�g���N�^���ĂׂȂ�
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
	* @param[in] hit_point�@�L������HP�@�g��������̂���
	*/
	virtual void initialize(int hit_point) = 0;

	/**
	* @brief �s����Ԃ̊Ǘ����\�b�h
	* @note  ���t���[���̏���
	*/
	virtual void update() = 0;

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief ���W���擾���ĕԂ�
	*/
	VECTOR GetPos() { return position; };
	// �ȏ�擾�p�萔===================================================================== //
protected:
	/**
	* @brief unordered_map���������\�b�h
	* @note  �eState���Ƃ̃��\�b�h��o�^
	*/
	virtual void initializeStateFunctions() = 0;

	/**
	* @brief ���W�Ɠ����蔻���ݒ肷�郁�\�b�h
	* @note  �ړ����ɌĂяo��
	*/
	virtual void updateMoveAndCollision() = 0;
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);			// ���W
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);			// �ړ��̌����x�N�g��
	VECTOR	obbTrans = VGet(0.f, 0.f, 0.f);			// �����蔻��OBB�̈ړ��l
	VECTOR	obbAngle = VGet(0.f, 0.f, 0.f);			// �����蔻��OBB�̉�]�l
	int		animHandle = 0;							// ���f���n���h��
	int		animNum = 0;							// �A�j���[�V�����ԍ�
	float   *animTimes = 0;							// �A�j���[�V�����̑��Đ�����
	float	animTimer = 0.f;						// �A�j���[�V�����̌��݂̍Đ�����
	float	angle = 0.f;							// ����		�A�^�b�`����rad�ɕϊ�
	float	hitPoint = 100.f;						// HP
	float	currentHP = 0.f;						// HP���ω��������𔻒f����p�̕ϐ�
	//float damage
	bool	isDeath = false;						// ���S�t���O

	typedef std::function<void()> StateFunction;	// �֐��|�C���^�̌^���`
};