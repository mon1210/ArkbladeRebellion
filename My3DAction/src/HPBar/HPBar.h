/**
* @file		HPBar.h
* @brief	�N���X HPBar �̐錾
*/
#pragma once
#include "..\Constants.h"
#include "..\Game\Game.h"

class Game;

class HPBar
{
public:
	/*
	* @brief HPBar�̃R���X�g���N�^
	*/
	HPBar(Game *Game_);
	~HPBar();
	/*
	* @brief �`�惁�\�b�h
	* @note  �̗͒ቺ�Ńo�[�̐F�ύX
	*/
	void draw();
	/*
	* @brief �ϓ�����
	* @note  ���炩��HP�̑���������
	*/
	void update();
private:
	Game	*pGame = nullptr;
	float	hpRatio = 0.f;	// HP�o�[�̕\���䗦

};
