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
	~Player() override;
	bool isAlive() override;								// �������ɂ����ʂƂ��ĕԂ��@true:���� / false:���S
	void draw() override;									// �`�惁�\�b�h
	void update() override;									// �s���Ǘ����\�b�h
	// �ȉ��擾�p�萔====================================================================== //
	float	GetHp();										// hitPoint���擾���ĕԂ�
	// �ȏ�擾�p�萔====================================================================== //
private:
	void initializeStateFunctions() override;				// unordered_map���������\�b�h�@�eState���Ƃ̊֐��o�^	
	void initializeAnimationList() override;				// animationList���������\�b�h
	bool checkMoveKey();									// �ړ��L�[�`�F�b�N�@���������Ȍ���
	bool checkRollKey();									// �O�]�L�[�`�F�b�N�@���������Ȍ���
	void animateAndMove(ePlayer::AnimationNum num,
		float ROTATE_ANGLE, float move_x, float move_z);	// �ړ����̍s���Ǘ����\�b�h
private:
	// ��Ԃ��Ƃ̃��\�b�h
	void idle();	// �ҋ@
	void move();	// �ړ�
	void roll();	// �O�](���)
	void attack();	// �U�� => �O�i�U���̗\��
	void damage();	// ��_���[�W
	void healing();	// ��
	void death();	// ���S
protected:
	Game	*pGame = nullptr;
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);								// �ړ��̌����x�N�g��
	int		rollCoolTime = 0;
	bool	isMove = false;												// �ړ��t���O
	bool	rollAble = true;											// Roll�\�t���O

	float* animTimes = 0;

	PlayerState currentState = PlayerState::Idle;						// ��Ԃ�\��

	std::unordered_map<PlayerState, StateFunction> stateFunctionMap;	// �֐��̓�����unordered_map���`

	std::vector<int> animationList;
};


// �}�N����`
#define VECTOR_SCALING	0.70710678118f	// �΂ߓ��͗p�̊e���̔{��( sin( 45��) )
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_ForwardRoll		CheckHitKey(KEY_INPUT_W)
#define Key_RightRoll		CheckHitKey(KEY_INPUT_D)
#define Key_LeftRoll		CheckHitKey(KEY_INPUT_A)