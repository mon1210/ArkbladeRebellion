/*
* @file		BG.h
* @brief	�N���X BG �̐錾
* @note		���͂����ŊǗ�
*/
#pragma once
#include "DxLib.h"
#include "stdafx.h"
#include "Game.h"

class Game;

class BG
{
public:
	BG(Game *Game_);
	~BG();
	void draw();							// �`�惁�\�b�h
	int  getModelHandle();					// ���f���擾�֐�
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// ���W
	int		tileHandle = 0;					// ���f���ۑ��p�ϐ�
};
