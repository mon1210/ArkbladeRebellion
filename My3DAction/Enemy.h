/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"

//--- �w�b�_�K�[�h���g�p���ē�x�C���N���[�h����̂�h��
#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class Stage;

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	virtual bool move() override;
	virtual void draw() override;
	virtual void SetMove();
	virtual void SetAnim(eEnemy::AnimationNum num);
	VECTOR	position;
protected:
	int		anim_handle;
	int		anim_no;
	float	anim_time;
	float	anim_timer;
	float	angle;
	float	hitPoint;
	//VECTOR	position;

private:

};