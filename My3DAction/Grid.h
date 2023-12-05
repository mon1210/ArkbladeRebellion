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
	virtual void Draw();	// �`�惁�\�b�h
protected:
	VECTOR startHorizontal;		// ���������̊J�n�n�_
	VECTOR endHorizontal;		// ���������̍ŏI�n�_ 
	VECTOR startVertical;		// ���������̊J�n�n�_
	VECTOR endVertical;			// ���������̍ŏI�n�_
};
