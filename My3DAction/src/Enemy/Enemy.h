/**
* @file		Enemy.h
* @brief	�N���X Enemy �̐錾
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
#include "..\OBBCollider\OBBCollider.h"

// �N���X�̑O���錾
class CharaBase;
class Game;
class OBBCollider;

class Enemy : public CharaBase
{
public:
	/**
	* @brief Enemy�̃R���X�g���N�^
	*/
	Enemy(Game *Game_);

	// �f�X�g���N�^
	~Enemy() override;

	/**
	* @brief  �������ɂ����ʂƂ��ĕԂ�
	* @return true:���� / false:���S
	*/
	bool isAlive() override;

	/**
	* @brief �`�惁�\�b�h
	*/
	void draw() override;

	/**
	* @brief ���������\�b�h
	* @param[in] hit_point�@�L������HP�@�g��������̂���
	*/
	void initialize(int hit_point) override;

	/**
	* @brief �s����Ԃ̊Ǘ����\�b�h
	* @note  ���t���[���̏���
	*/
	void update() override;

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief pOBBCol���擾���ĕԂ�
	*/
	OBBCollider *GetOBBCol();
	// �ȏ�擾�p�萔===================================================================== //
private:
	/**
	* @brief unordered_map���������\�b�h
	* @note  �eState���Ƃ̃��\�b�h��o�^
	*/
	void initializeStateFunctions() override;

	/**
	* @brief   �G�l�~�[�̎��상�\�b�h
	* @return  true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������
	*/
	bool isTargetVisible();

	/**
	* @brief enemyToPlayer�̍X�V�E�������Z�o�@���t���[���Ăяo��
	* @note  ���t���[���̏���
	*/
	void updateToPlayerVec();

	/**
	* @brief ��ԂƃA�j���[�V������ݒ�
	* @note  ��ԕύX���Ɏg�p
	* @param[in] state  �ύX��̏��
	* @param[in] num    �ύX��̃A�j���[�V����
	*/
	void setStateAndAnim(EnemyState state,eEnemy::AnimationNum anim_num);	// ��ԂƃA�j���[�V������ݒ�

	/**
	* @brief ���W�Ɠ����蔻���ݒ肷�郁�\�b�h
	* @note  �ړ����ɌĂяo��
	*/
	void updateMoveAndCollision() override;

	// ��Ԃ��Ƃ̃��\�b�h
	void wait();	// �ҋ@
	void move();	// �ړ�
	void chase();	// �ǐ�
	void attack();	// �U��
	void damage();	// ��_���[�W
	void death();	// ���S
private:
	Game		*pGame = nullptr;
	OBBCollider *pOBBCol = nullptr;
	OBBCollider *pOBBColHand = nullptr;
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);						// �G�l�~�[����v���C���[�܂ł̋���
	int		count = 0;												// �t���[���v���p�@�s���J��, �Ŏg�p 
	float   vecLength = 0.f;										// �x�N�g���̒����ۑ��p
	float	animTime = 0.f;											// �A�j���[�V�������ԕۑ��p�ϐ��@Enemy�͖��t���[����ԕϐ���ʂ�Ȃ��̂ŕK�v
	bool	isColHit = false;										// �����蔻�肪�ڐG�������ǂ���
	bool	isAttack = false;										// �U����Ԃ��ǂ���

	EnemyState currentState = EnemyState::Wait;						// ��Ԃ�\��

	std::unordered_map<EnemyState, StateFunction> stateFunctionMap;	// �֐��̓�����unordered_map���`
};