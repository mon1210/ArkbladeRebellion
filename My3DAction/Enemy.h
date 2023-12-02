/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
* @note		�����蔻�� () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "IGameObject.h"

class Model;
class BG;

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	virtual void InitAnimation();
	virtual void Update();
	virtual bool IsTargetVisible();
	virtual bool move() override;	// �G�l�~�[�̃A�j���[�V�������\�b�h�@true:���� / false:���S
	virtual void draw() override;	// �`�惁�\�b�h
	virtual void SetMove();		// �s���Ǘ��֐�
	virtual void SetAnim(eEnemy::AnimationNum num);		// �A�j���[�V�����Z�b�g�֐�
	virtual VECTOR GetEnemyPos();	// ���W�擾�֐�
private:
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	Model*	pModel;
	BG*		pBG;
	VECTOR	position;
	int		animHandle;
	int		animNo;
	int		count;		// �t���[���v���p�@�s���J��, �Ŏg�p 
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;

	EnemyState currentState;
private:


};