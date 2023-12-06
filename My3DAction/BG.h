/*
* @file		BG.h
* @brief	�N���X BG �̐錾
* @note		����͂����ŊǗ�
*/
#pragma once
#include "DxLib.h"
#include "stdafx.h"
#include "IGameObject.h"

class BG
{
public:
	BG();
	virtual ~BG();
	virtual void draw();			// �`�惁�\�b�h
	virtual int GetModelHandle();	// ���f���擾�֐�
	virtual void setTileModel(int model);	// �^�C�����f�����Z�b�g����
protected:
	VECTOR	position;		// ���W
	int		tile_handle;	// ���f���ۑ��p�ϐ�
};
