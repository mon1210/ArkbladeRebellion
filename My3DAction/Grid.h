/*
* @file		Grid.h
* @brief	�N���X Grid �̐錾
* @note		3D���f���̈ʒu�����o�I�ɂ킩��₷�����邽�߂ɁA�n�ʂɃ��C����\������
*/
#pragma once
#include "Constants.h"
#include "DxLib.h"


class Grid
{
public:
	Grid();
	~Grid();
	virtual void draw();	// �`�惁�\�b�h
protected:
	VECTOR startHorizontal = VGet(0.f, 0.f, 0.f);	// ���������̊J�n�n�_
	VECTOR endHorizontal = VGet(0.f, 0.f, 0.f);		// ���������̍ŏI�n�_ 
	VECTOR startVertical = VGet(0.f, 0.f, 0.f);		// ���������̊J�n�n�_
	VECTOR endVertical = VGet(0.f, 0.f, 0.f);		// ���������̍ŏI�n�_
};
