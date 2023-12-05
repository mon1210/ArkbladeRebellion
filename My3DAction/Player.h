/*
* @file		Player.h
* @brief	�N���X Player �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "Constants.h"
#include "Collider.h"
#include "Stage.h"
#include "IGameObject.h"

// �N���X�̑O���錾
class Stage;
class Collider;

class Player : public IGameObject
{
public:
	Player(Stage *parent);
	~Player();
	virtual bool move() override;	// �A�j���[�V�������\�b�h
	virtual void draw() override;	// �`�惁�\�b�h
	virtual void SetMove();			// �s���Ǘ����\�b�h
	virtual void SetAnim(ePlayer::AnimationNum num);  // �A�j���[�V�����Z�b�g���\�b�h
	virtual void RollAnim();		// Roll�̃A�j���[�V�������\�b�h
	VECTOR  GetPlayerPos();			// ���W���擾���ĕԂ����\�b�h
	VECTOR  GetPlayerMoveVec();		// Player�̈ړ��������擾���ĕԂ����\�b�h
	virtual void setPlayerModel(int model);				// �v���C���[�̃��f�����Z�b�g���郁�\�b�h
	virtual void setCameraHAngle(float camera_H_A);		// �J�����̐��������̊p�x���Z�b�g���郁�\�b�h
	virtual void setPlayerNewPos(VECTOR new_pos);		// �v���C���[�̈ړ���̐V�������W���Z�b�g���郁�\�b�h
protected:
	Collider *pCollider;
	VECTOR	position;	// ���W
	VECTOR  newPos;		// �ړ���̐V�K���W
	VECTOR	moveVec;	// �ړ��̌����x�N�g��
	int		animHandle;	// ���f���n���h��
	int		animNo;		// �A�j���[�V�����ԍ�
	float	animTime;	// �A�j���[�V�����̑��Đ�����
	float	animTimer;	// �A�j���[�V�����̌��݂̍Đ�����
	float	angle;		// �v���C���[�̌���
	float	hitPoint;	// HP
	float   cameraHA;	// �J�����̐����p�x  CameraHorizontalAngle
	bool	moveFlag;	// �ړ��t���O
	bool	rollAble;	// Roll�\�t���O
};


// �}�N����`
#define VECTOR_SCALING	0.70710678118f	// �΂ߓ��͗p�̊e���̔{��( sin( 45��) )
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_Roll			CheckHitKey(KEY_INPUT_SPACE)