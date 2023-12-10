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
#include "Stage.h"
#include "Radar.h"
#include "Constants.h"
#include "IGameObject.h"

// �N���X�̑O���錾
class Stage;
class Radar;

class Enemy : public IGameObject
{
public:
	Enemy(Stage *parent);
	~Enemy();
	void initAnimation();	// �A�j���[�V������ԏ������֐� Stage�ŏ���������x�����Ăяo��
	void update();			// ��ԊǗ���draw�Ăяo���@���t���[���Ăяo�����
	bool isTargetVisible();	// �G�l�~�[�̎���@true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������ 
	bool move() override;	// �G�l�~�[�̃A�j���[�V�������\�b�h�@true:���� / false:���S
	void draw() override;	// �`�惁�\�b�h
	void setAnim(eEnemy::AnimationNum num);	// �A�j���[�V�����Z�b�g���\�b�h
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