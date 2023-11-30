#pragma once
#include "DxLib.h"

#ifndef __IGAMEOBJECT_H__
//�Q�[����̃I�u�W�F�N�g��\������N���X��ĉ������C���^�[�t�F�[�X�̐錾
#include "IGameObject.h"
#endif

class Model;

class BG
{
public:
	BG();
	virtual ~BG();
	virtual void draw();
	virtual int GetModelHandle();
protected:
	Model*	pModel;
	int		tile_handle;
	VECTOR	position;
};
