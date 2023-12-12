/*
* @file		BG.h
* @brief	�N���X BG �̐錾
* @note		���͂����ŊǗ�
*/
#pragma once
#include "DxLib.h"
#include "stdafx.h"

class BG
{
public:
	BG();
	~BG();
	void draw();					// �`�惁�\�b�h
	void setTileModel(int model);	// �^�C�����f�����Z�b�g����
	int  getModelHandle();			// ���f���擾�֐�
protected:
	VECTOR	position;		// ���W
	int		tile_handle;	// ���f���ۑ��p�ϐ�
};
