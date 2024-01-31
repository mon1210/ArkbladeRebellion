/**
* @file		Collision.h
* @brief	�N���X Collision �̐錾
* @note		�v���C���[�E���ɑ΂��ĉe������̂�Game�Ŋ֐��g�p
*/
#pragma once
#include "DxLib.h"
#include "..\Game\Game.h"

// �N���X�̑O���錾
class Game;

class Collision
{
public:
	/**
	* @brief Collision�̃R���X�g���N�^
	*/
	Collision(Game *Game_);

	// �f�X�g���N�^
	~Collision();

	/**
	* @brief �����蔻�菉����
	* @note  ���ɓ����蔻��t�^
	*/
	void initialize(int handle);

	/**
	* @brief  �ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
	* @note   �ړ��͈͂𐧌����Ă���
	* @return true:���肠��A�ړ��� / false:����Ȃ��A�ړ��s��
	*/
	bool clampToStageBounds(VECTOR& new_pos, VECTOR& pos);

	/**
	* @brief  �L�������m�̃J�v�Z�������蔻�胁�\�b�h
	* @note   �L�����̈ړ����ɌĂяo���Ă���
	* @return true:�������Ă��� / false:�������Ă��Ȃ�
	* @param[in] pos1�@			�ړ����Ă���L�����̍��W
	* @param[in] pos1_move_vec�@�ړ����Ă���L�����̈ړ��x�N�g��
	* @param[in] pos2�@			�������鑤�̍��W
	* @param[in] cap1_height�@	pos1�̃J�v�Z���̍���
	* @param[in] cap2_height�@	pos2�̃J�v�Z���̍���
	* @param[in] cap1_radius�@	pos1�̃J�v�Z���̔��a
	* @param[in] cap2_radius�@	pos2�̃J�v�Z���̔��a
	*/
	bool charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR pos2,
		float cap1_height, float cap2_height, float cap1_radius, float cap2_radius);

	/**
	* @brief  �L�����N�^�[���U���͈͓��ɂ��邩�����𔻒肷�郁�\�b�h
	* @note
	* @return true:�U���͈͂̒� / false:�U���͈͂̊O
	* @param[in] attack_ch_pos�@�U�����悤�Ƃ��Ă���L�����̍��W
	* @param[in] damage_ch_pos�@�U�����󂯂悤�Ƃ��Ă���L�����̍��W
	* @param[in] attack_area�@	�U���͈�
	*/
	bool checkAttackArea(VECTOR attack_ch_pos, VECTOR damage_ch_pos, float attack_area);

private:
	/**
	* @brief  ��������₪�A���������ǂ����𔻒f
	* @note	  OBB�̓��e�����Ɠ�̋�����r
	*
	* @return true:�������ł��� / false:�������ł͂Ȃ�
	* @param[in] axis�@			���������
	* @param[in] obb1_vertices�@��ڂ�OBB�̒��_
	* @param[in] obb2_vertices�@��ڂ�OBB�̒��_
	*/
	bool isFindSeparatingAxis(const VECTOR& axis, VECTOR obb1_vertices[8], VECTOR obb2_vertices[8]);
private:
	Game *pGame = nullptr;
	int tileHandle = 0;		// �����f���ۑ��p

};