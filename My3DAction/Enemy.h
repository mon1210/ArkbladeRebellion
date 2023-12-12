/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "CharaBase.h"

#include "BG.h"
#include "Player.h"
#include "Animation.h"
#include "Constants.h"
#include "Enums.h"
#include "Game.h"
#include "Radar.h"

// �N���X�̑O���錾
class CharaBase;
class Game;
class Radar;

class Enemy : public CharaBase
{
public:
	Enemy(Game *parent);
	~Enemy();
	void initAnimation();	// �A�j���[�V������ԏ������֐� Stage�ŏ���������x�����Ăяo��
	bool move() override;	// �G�l�~�[�̃A�j���[�V�������\�b�h�@true:���� / false:���S
	void draw() override;	// �`�惁�\�b�h
	void update() override;	// ��ԊǗ���draw�Ăяo���@���t���[���Ăяo�����
	bool isTargetVisible();	// �G�l�~�[�̎���@true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������ 
	void animationHandle(eEnemy::AnimationNum num);	// �A�j���[�V������ݒ肷��
	void setEnemyModel(int model);			// �G�l�~�[�̃��f�����Z�b�g����
	void setTileModel(int model);			// �����f�����Z�b�g����@ �� => �����蔻��Ŏg�p
	void setPlayerPos(VECTOR player_pos);	// �v���C���[�̍��W���Z�b�g����
	VECTOR getEnemyPos();	// ���W�擾���\�b�h
private:
	// ��Ԃ��Ƃ̃��\�b�h
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	Radar	*pRadar;
	VECTOR  playerPos;		// enemyToPlayer�����߂�̂Ɏg�p
	VECTOR  enemyToPlayer;	// �G�l�~�[����v���C���[�܂ł̋���
	int		tileHandle;
	int		count;			// �t���[���v���p�@�s���J��, �Ŏg�p 
	float	hitPoint;
	float   vecLength;		// �x�N�g���̒����ۑ��p

	EnemyState currentState;
};