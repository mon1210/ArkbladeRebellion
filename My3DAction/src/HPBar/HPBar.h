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
	HPBar(Game *Game_);
	~HPBar();
	void update();			// UI�̕ϓ��p���\�b�h
	void draw();			// �`��p���\�b�h
private:
protected:
	Game	*pGame = nullptr;
	float	hpRatio = 0.f;	// HP�o�[�̕\���䗦

};
