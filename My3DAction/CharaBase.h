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
	virtual VECTOR getPos() = 0;
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// ���W
	int		animHandle = 0;					// ���f���n���h��
	int		animNo = 0;						// �A�j���[�V�����ԍ�
	float	animTime = 0.f;					// �A�j���[�V�����̑��Đ�����
	float	animTimer = 0.f;				// �A�j���[�V�����̌��݂̍Đ�����
	float	angle = 0.f;					// ����		�A�^�b�`����rad�ɕϊ�
	float	hitPoint = 100.f;				// HP
	//float damage
};