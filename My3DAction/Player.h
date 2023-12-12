/*
* @file		Player.h
* @brief	�N���X Player �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "CharaBase.h"

#include "Animation.h"
#include "Constants.h"
#include "Collision.h"
#include "Enums.h"
#include "Game.h"
#include "Radar.h"

// �N���X�̑O���錾
class CharaBase;
class Game;
class Collision;
class Radar;

class Player : public CharaBase
{
public:
	Player(Game *parent);
	~Player();
	bool move() override;	// �A�j���[�V�������\�b�h
	void draw() override;	// �`�惁�\�b�h
	void update() override;	// �s���Ǘ����\�b�h
	void moveHandle(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z);	// �ړ����̍s���Ǘ����\�b�h
	VECTOR  getPlayerPos();			// ���W���擾���ĕԂ����\�b�h
	VECTOR  getPlayerMoveVec();		// Player�̈ړ��������擾���ĕԂ����\�b�h
	void setPlayerModel(int model);				// �v���C���[�̃��f�����Z�b�g���郁�\�b�h
	void setCameraHAngle(float camera_H_A);		// �J�����̐��������̊p�x���Z�b�g���郁�\�b�h
	void setPlayerNewPos(VECTOR new_pos);		// �v���C���[�̈ړ���̐V�������W���Z�b�g���郁�\�b�h
protected:
	Collision *pCollision;
	Radar	  *pRadar;
	VECTOR  newPos;		// �ړ���̍��W�ۑ��p
	VECTOR	moveVec;	// �ړ��̌����x�N�g��
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