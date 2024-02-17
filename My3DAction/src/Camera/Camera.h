/**
* @file		Camera.h
* @brief	�N���X Camera �̐錾
* @note		�v���C���[��Ǐ]����
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"
#include <math.h>

class Game;

class Camera
{
public:
	/**
	* @brief Camera�̃R���X�g���N�^
	*/
	Camera(Game *Game);

	/**
	* @brief Camera�̃f�X�g���N�^
	*/
	~Camera();

	/**
	* @brief �J�����̍X�V
	*/
	void update();

	/**
	* @brief   �v���C���[�̈ʒu�Z�o���\�b�h
	* @note    �J�����̊p�x�ɍ��킹��̂�Camera�N���X�Œ�`
	* @return  NewPlayerPos
	*/
	VECTOR moveAlongHAngle(VECTOR move_vec, VECTOR player_pos);

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief �J���������p�x���擾���ĕԂ�
	*/
	float GetHorizontalAngle();
	// �ȏ�擾�p�萔===================================================================== //
private:
	/**
	* @brief �J�������상�\�b�h
	*/
	void control();

	/**
	* @brief �ʒu�Z�o���\�b�h
	*/
	void setPosition(VECTOR player_pos);
private:
	Game	*pGame = nullptr;
	//! ���W
	VECTOR	position = VGet(0.f, 0.f, 0.f);
	//! ���������̊p�x
	float	hAngle = 0.f;
	//! ���������̊p�x
	float	vAngle = 40.f;
};

