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
	virtual ~CharaBase();
	virtual bool isAlive() = 0;						// �������ɂ����ʂƂ��ĕԂ��@true:���� / false:���S
	virtual void draw() = 0;						// �`�惁�\�b�h
	virtual void initialize(int hit_point) = 0;		// ���������\�b�h
	virtual void update() = 0;						// �X�V���\�b�h
	virtual void initializeStateFunctions() = 0;	// unordered_map���������\�b�h�@�eState���Ƃ̊֐��o�^
	// �ȉ��擾�p�萔===================================================================== //
	VECTOR GetPos() { return position; };			// ���W���擾���ĕԂ�
	// �ȏ�擾�p�萔===================================================================== //
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);			// ���W
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);			// �ړ��̌����x�N�g��
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