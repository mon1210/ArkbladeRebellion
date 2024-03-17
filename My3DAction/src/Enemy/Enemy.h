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

//! �N���X�̑O���錾
class CharaBase;
class Game;
class OBBCollider;

class Enemy : public CharaBase
{
public:
	/**
	* @brief Enemy�̃R���X�g���N�^
	*/
	Enemy(Game *Game);

	/**
	* @brief Enemy�̃f�X�g���N�^
	*/
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
	* @note  �g�������l����������HP���w��
	* @param[in] hit_point  �L������HP
	*/
	void initialize(int hit_point) override;

	/**
	* @brief �s����Ԃ̊Ǘ����\�b�h
	* @note  ���t���[���̏���
	*/
	void update() override;

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief mOBBCol���擾���ĕԂ�
	*/
	OBBCollider GetOBBCol();
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
	void setStateAndAnim(EnemyState state, eEnemy::AnimationNum anim_num);

	/**
	* @brief �ړ���̍��W��ݒ肷��
	* @note  �ړ����ɌĂяo��
	*/
	void moveHandle() override;

	// �ȉ� ��Ԃ��Ƃ̃��\�b�h ---------------------
	/**
	* @brief �ҋ@��Ԃ̊Ǘ����\�b�h
	*/
	void wait();

	/**
	* @brief �ړ���Ԃ̊Ǘ����\�b�h
	*/
	void move();

	/**
	* @brief �ǐՏ�Ԃ̊Ǘ����\�b�h
	*/
	void chase();

	/**
	* @brief �U����Ԃ̊Ǘ����\�b�h
	*/
	void attack();

	/**
	* @brief ��_���[�W��Ԃ̊Ǘ����\�b�h
	*/
	void damage();

	/**
	* @brief ���S��Ԃ̊Ǘ����\�b�h
	*/
	void death();
	// �ȏ� ��Ԃ��Ƃ̃��\�b�h ---------------------
private:
	//! OBBCollider�C���X�^���X��   ��_���[�W���g�p�@��
	OBBCollider mOBBCol = OBBCollider(ENEMY_OBB_SCALE, ENEMY_OBB_ANGLE, ENEMY_OBB_TRANS);

	//! OBBCollider�C���X�^���X��   �U�����g�p�@��
	OBBCollider mOBBColHand = OBBCollider(HAND_OBB_SCALE, HAND_OBB_ANGLE, HAND_OBB_TRANS);
private:
	Game	*pGame = nullptr;
	//! �G�l�~�[����v���C���[�܂ł̋���
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);
	//! �t���[���v���p�@�s���J��, �Ŏg�p 
	int		count = 0;
	//! �x�N�g���̒����ۑ��p
	float   vecLength = 0.f;
	//! �A�j���[�V�������ԕۑ��p�ϐ��@Enemy�͖��t���[����ԕϐ���ʂ�Ȃ��̂ŕK�v
	float	animTime = 0.f;
	//! �����蔻�肪�ڐG�������ǂ���
	bool	isColHit = false;
	//! �U����Ԃ��ǂ���
	bool	isAttack = false;

	//! ��Ԃ�\��
	EnemyState currentState = EnemyState::Wait;

	//! �֐��̓�����unordered_map���`
	std::unordered_map<EnemyState, stateFunction> stateFunctionMap;
};