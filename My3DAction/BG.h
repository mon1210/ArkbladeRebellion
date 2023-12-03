#pragma once
#include "DxLib.h"
#include "IGameObject.h"

class Model;

class BG
{
public:
	BG();
	virtual ~BG();
	virtual void draw();	// �`�惁�\�b�h
	virtual int GetModelHandle();	// ���f���擾�֐�
protected:
	Model*	pModel;
	VECTOR	position;		// ���W
	int		tile_handle;	// ���f���ۑ��p�ϐ�
};
