/**
* @file		HealCounter.h
* @brief	�N���X HealCounter �̐錾
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"

//! �N���X�̑O���錾
class Game;

class HealCounter
{
public:
	/**
	* @brief HealCounter�̃R���X�g���N�^
	*/
	HealCounter(Game *Game);

	/**
	* @brief HealCounter�̃f�X�g���N�^
	*/
	~HealCounter();

	/**
	* @brief �`�惁�\�b�h
	*/
	void draw();

	/**
	* @brief �X�V���\�b�h
	* @note  �c��񐔂ɍ��킹�ĐF�ύX
	*/
	void update();
private:
	Game *pGame = nullptr;
	//! UI�̐F
	unsigned int color = 0;
};
