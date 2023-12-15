/**
* @file		CharaBase.h
* @brief	�N���XCharaBase�̐錾�t�@�C��
* @note		Character�̊��N���X�ŁAPlayer��Enemy���p�����Ă���
*			���N���X�ł́A���ʂ���֐��ƕϐ����܂Ƃ߂Đ錾
*/
#pragma once
#include "DxLib.h"

// ���N���X
class CharaBase 
{
public:
	virtual ~CharaBase();
	virtual bool move() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void setModel(int model) = 0;
	virtual VECTOR getPos() = 0;
protected:
	VECTOR	position;	// ���W
	int		animHandle;	// ���f���n���h��
	int		animNo;		// �A�j���[�V�����ԍ�
	float	animTime;	// �A�j���[�V�����̑��Đ�����
	float	animTimer;	// �A�j���[�V�����̌��݂̍Đ�����
	float	angle;		// ����		�A�^�b�`����rad�ɕϊ�
	float	hitPoint;	// HP
	//float damage
};