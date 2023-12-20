/**
* @file		UI.h
* @brief	�N���X UI �̐錾
*/
#pragma once
#include "..\Constants.h"
#include "..\Game\Game.h"

class Game;

class UI
{
public:
	UI(Game *Game_);
	~UI();
	void move();			// UI�̕ϓ��p���\�b�h
	void draw();			// �`��p���\�b�h
private:
protected:
	Game	*pGame = NULL;
	float	hpRatio = 0.f;	// HP�o�[�̕\���䗦

};

#define GREEN GetColor(0, 255, 0) 
#define WHITE GetColor(255, 255, 255)