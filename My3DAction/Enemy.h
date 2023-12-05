/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "BG.h"
#include "Player.h"
#include "Constants.h"
#include "IGameObject.h"


class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	virtual void InitAnimation();	// �A�j���[�V������ԏ������֐� Stage�ŏ���������x�����Ăяo��
	virtual void Update();			// ��ԊǗ���draw�Ăяo���@���t���[���Ăяo�����
	virtual bool IsTargetVisible();	// �G�l�~�[�̎���@true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������ 
	virtual bool move() override;	// �G�l�~�[�̃A�j���[�V�������\�b�h�@true:���� / false:���S
	virtual void draw() override;	// �`�惁�\�b�h
	virtual void SetMove();			// �s���Ǘ����\�b�h�@�f�o�b�O�p�@�폜�\�� Todo
	virtual void SetAnim(eEnemy::AnimationNum num);	// �A�j���[�V�����Z�b�g���\�b�h
	virtual VECTOR GetEnemyPos();	// ���W�擾���\�b�h
	virtual void setEnemyModel(int model);			// �G�l�~�[�̃��f�����Z�b�g����
	virtual void setTileModel(int model);			// �^�C���̃��f�����Z�b�g����@ �^�C�� => �����蔻��Ŏg�p
	virtual void setPlayerPos(VECTOR player_pos);	// �v���C���[�̍��W���Z�b�g����
private:
	// ��Ԃ��Ƃ̃��\�b�h
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	VECTOR	position;
	VECTOR  playerPos;		// enemyToPlayer�����߂�̂Ɏg�p
	VECTOR  enemyToPlayer;	// �G�l�~�[����v���C���[�܂ł̋���
	int		animHandle;
	int		tileHandle;
	int		animNo;
	int		count;			// �t���[���v���p�@�s���J��, �Ŏg�p 
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;
	float   vecLength;		// �x�N�g���̒����ۑ��p

	EnemyState currentState;
private:


};