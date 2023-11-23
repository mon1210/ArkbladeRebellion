/**
* @file IGameObject.h
* @brief �Q�[����̃I�u�W�F�N�g��\������N���X��ĉ������C���^�[�t�F�[�X�̐錾
* @note ���{�̃Q�[���ƊE�ł̓^�X�N�ƌĂԏꍇ������
*/
#pragma once
#define __IGAMEOBJECT_H__

typedef struct {
	float x;	//	�N�_
	float y;	//	�N�_
	float z;	//	�N�_
	float vx;	//	x����
	float vy;	//	y����
	float vz;	//	z����
}	STEP_VECTOR;


class IGameObject
{
public:
	virtual ~IGameObject() = 0;
	virtual bool move() = 0;
	virtual void draw() = 0;
	//virtual int damage(float amount) = 0;

	STEP_VECTOR step;
	float	Damage;
};

//  �}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }
