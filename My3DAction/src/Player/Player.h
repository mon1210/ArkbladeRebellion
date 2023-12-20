/*
* @file		Player.h
* @brief	�N���X Player �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "..\CharaBase\CharaBase.h"

#include "..\Animation\Animation.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\Game\Game.h"

// �N���X�̑O���錾
class CharaBase;
class Game;

class Player : public CharaBase
{
public:
	Player(Game *Game_);
	~Player();
	bool isAlive() override;								// �������ɂ����ʂƂ��ĕԂ��@true:���� / false:���S
	void draw() override;									// �`�惁�\�b�h
	void update() override;									// �s���Ǘ����\�b�h
	void animateAndMove(ePlayer::AnimationNum num,
		float ROTATE_ANGLE, float move_x, float move_z);	// �ړ����̍s���Ǘ����\�b�h
	// �ȉ��擾�p�萔====================================================================== //
	VECTOR  GetPos() override;								// ���W���擾���ĕԂ����\�b�h
	float	GetHp();										// 
	// �ȏ�擾�p�萔====================================================================== //
protected:
	Game	*pGame = NULL;
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);	// �ړ��̌����x�N�g��
	bool	isMove = false;					// �ړ��t���O
	bool	rollAble = true;				// Roll�\�t���O
};


// �}�N����`
#define VECTOR_SCALING	0.70710678118f	// �΂ߓ��͗p�̊e���̔{��( sin( 45��) )
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_Roll			CheckHitKey(KEY_INPUT_SPACE)