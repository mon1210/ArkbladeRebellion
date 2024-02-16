/*
* @file		BG.h
* @brief	�N���X BG �̐錾
* @note		���͂����ŊǗ�
*/
#pragma once
#include "DxLib.h"
#include "..\stdafx.h"
#include "..\Game\Game.h"

class Game;

class BG
{
public:
	/**
	* @brief BG�̃R���X�g���N�^
	*/
	BG(Game *Game);

	// �f�X�g���N�^
	~BG();

	/**
	* @brief �`�惁�\�b�h
	* @note  ��ʏ�Ɍ����Ă��镔���̂ݕ`��
	*/
	void draw();

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief �����f�����擾���ĕԂ�
	*/
	int  GetModelHandle();
	// �ȏ�擾�p�萔===================================================================== //
private:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// ���W
	int		tileHandle = 0;					// �����f���ۑ��p
};
