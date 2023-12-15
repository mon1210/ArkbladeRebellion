/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "CharaBase.h"

#include <math.h>
#include "BG.h"
#include "Player.h"
#include "Animation.h"
#include "Constants.h"
#include "Enums.h"
#include "Game.h"

// �N���X�̑O���錾
class CharaBase;
class Game;

class Enemy : public CharaBase
{
public:
	Enemy(Game *Game_);
	~Enemy();
	void initAnimation();		// �A�j���[�V������ԏ������֐� Stage�ŏ���������x�����Ăяo��
	bool move() override;		// �G�l�~�[�̃A�j���[�V�������\�b�h�@true:���� / false:���S
	void draw() override;		// �`�惁�\�b�h
	void update() override;		// ��ԊǗ���draw�Ăяo���@���t���[���Ăяo�����
	VECTOR getPos() override;	// ���W�擾���\�b�h
	bool isTargetVisible();		// �G�l�~�[�̎���@true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������ 
	void animationHandle(eEnemy::AnimationNum num);	// �A�j���[�V������ݒ肷��
	void setPlayerPos(VECTOR player_pos);	// �v���C���[�̍��W���Z�b�g����

	void updateEnemyToPlayerVec() {		// enemyToPlayer�̍X�V�E�������Z�o�@���t���[���Ăяo��
		enemyToPlayer = VSub(playerPos, position);   // �G�l�~�[����v���C���[�̋����x�N�g�������߂�
		vecLength = sqrtf(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.z * enemyToPlayer.z); // �����x�N�g���̒���
	}
private:
	// ��Ԃ��Ƃ̃��\�b�h
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	Game	*pGame;
	VECTOR  playerPos;		// enemyToPlayer�����߂�̂Ɏg�p
	VECTOR  enemyToPlayer;	// �G�l�~�[����v���C���[�܂ł̋���
	int		tileHandle;
	int		count;			// �t���[���v���p�@�s���J��, �Ŏg�p 
	float	hitPoint;
	float   vecLength;		// �x�N�g���̒����ۑ��p

	EnemyState currentState;
};