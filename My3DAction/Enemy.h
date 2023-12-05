/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "IGameObject.h"

// �N���X�̑O���錾
class Stage;

class Enemy : public IGameObject
{
public:
	Enemy(Stage *parent);
	~Enemy();
	virtual void InitAnimation();
	virtual void Update();
	virtual bool IsTargetVisible();
	virtual bool move() override;	// �G�l�~�[�̃A�j���[�V�������\�b�h�@true:���� / false:���S
	virtual void draw() override;	// �`�惁�\�b�h
	virtual void SetMove();		// �s���Ǘ��֐�
	virtual void SetAnim(eEnemy::AnimationNum num);		// �A�j���[�V�����Z�b�g�֐�
	virtual VECTOR GetEnemyPos();	// ���W�擾�֐�
	virtual void setEnemyModel(int model);
	virtual void setTileModel(int model);
	virtual void setPlayerPos(VECTOR player_pos);
private:
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	VECTOR	position;
	VECTOR  playerPos;
	VECTOR  enemyToPlayer;	// �G�l�~�[����v���C���[�܂ł̋���
	int		animHandle;
	int		tileHandle;
	int		animNo;
	int		count;		// �t���[���v���p�@�s���J��, �Ŏg�p 
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;
	float   vecLength;	// �x�N�g���̒����ۑ��p

	EnemyState currentState;
private:


};