/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "..\CharaBase\CharaBase.h"

#include <math.h>
#include "..\BG\BG.h"
#include "..\Player\Player.h"
#include "..\Animation\Animation.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\Game\Game.h"

// �N���X�̑O���錾
class CharaBase;
class Game;

class Enemy : public CharaBase
{
public:
	Enemy(Game *Game_);
	~Enemy() override;
	bool isAlive() override;							// �������ɂ����ʂƂ��ĕԂ��@true:���� / false:���S
	void draw() override;								// �`�惁�\�b�h
	void initialize(int hit_point) override;			// ���������\�b�h
	void update() override;								// ��ԊǗ���draw�Ăяo���@���t���[���Ăяo�����
private:
	void initializeStateFunctions() override;			// unordered_map���������\�b�h�@�eState���Ƃ̊֐��o�^
	bool isTargetVisible();								// �G�l�~�[�̎���@true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������
	void updateToPlayerVec();							// enemyToPlayer�̍X�V�E�������Z�o�@���t���[���Ăяo��
	void setStateAndAnim(EnemyState state,
					 eEnemy::AnimationNum anim_num);	// ��ԂƃA�j���[�V������ݒ�
	// ��Ԃ��Ƃ̃��\�b�h
	void wait();	// �ҋ@
	void move();	// �ړ�
	void chase();	// �ǐ�
	void attack();	// 
protected:
	Game	*pGame = nullptr;
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);						// �G�l�~�[����v���C���[�܂ł̋���
	int		count = 0;												// �t���[���v���p�@�s���J��, �Ŏg�p 
	float   vecLength = 0.f;										// �x�N�g���̒����ۑ��p
	float	animTime = 0.f;											// �A�j���[�V�������ԕۑ��p�ϐ��@Enemy�͖��t���[����ԕϐ���ʂ�Ȃ��̂ŕK�v
	bool	isColHit = false;										// �����蔻�肪�ڐG�������ǂ���
	bool	isAttack = false;										// �U����Ԃ��ǂ���

	EnemyState currentState = EnemyState::Wait;						// ��Ԃ�\��

	std::unordered_map<EnemyState, StateFunction> stateFunctionMap;	// �֐��̓�����unordered_map���`
};