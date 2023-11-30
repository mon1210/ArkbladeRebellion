/*
* @file		Player.h
* @brief	�N���X Player �̐錾
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
class Camera;
class Collider;
class Model;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	virtual bool move() override;
	virtual void draw() override;
	virtual void SetMove();
	virtual void SetAnim(ePlayer::AnimationNum num);
	virtual void RollAnim();
	virtual VECTOR GetPlayerPos();	// ���W�擾�֐�
protected:
	Camera*		pCamera;
	Collider*	pCollider;
	Model*		pModel;
	VECTOR	position;	// ���W
	VECTOR	moveVec;	// �ړ��̌����x�N�g��
	int		animHandle;	// ���f���n���h��
	int		animNo;		// �A�j���[�V�����ԍ�
	float	animTime;	// �A�j���[�V�����̑��Đ�����
	float	animTimer;	// �A�j���[�V�����̌��݂̍Đ�����
	float	angle;		// �v���C���[�̌���
	float	hitPoint;	// HP
	bool	moveFlag;	// �ړ��t���O
	bool	rollAble;	// Roll�\�t���O
private:

};
