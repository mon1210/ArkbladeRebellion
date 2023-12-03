/*
* @file		Player.h
* @brief	�N���X Player �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "IGameObject.h"

class Stage;
class Camera;
class Collider;
class Model;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	virtual bool move() override;	// �A�j���[�V�������\�b�h
	virtual void draw() override;	// �`�惁�\�b�h
	virtual void SetMove();			// �s���Ǘ��֐�
	virtual void SetAnim(ePlayer::AnimationNum num);	// �A�j���[�V�����Z�b�g�֐�
	virtual void RollAnim();		// Roll�̃A�j���[�V�������\�b�h
	VECTOR*	GetPlayerPos();			// ���W�擾�֐�
protected:
	Camera*		pCamera;
	Collider*	pCollider;
	Model*		pModel;
	VECTOR	position;	// ���W
	VECTOR* pPlayerPos;	// 
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
