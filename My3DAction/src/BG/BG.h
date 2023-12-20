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
	BG(Game *Game_);
	~BG();
	void draw();							// �`�惁�\�b�h
	// �ȉ��擾�p�萔===================================================================== //
	int  GetModelHandle();					// ���f���擾�֐�
	// �ȏ�擾�p�萔===================================================================== //
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// ���W
	int		tileHandle = 0;					// �����f���ۑ��p
};
