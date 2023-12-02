/**
* @file		Title.h
* @brief	�N���X Title �̐錾
*/
#pragma once

#ifndef __IGAMESCENE_H__
#include "IGameScene.h"
#endif // !__IGAMEOBJECT_H__

enum TitlePhase {
	TITLE_INIT = 0,
	TITLE_RUN = 1,
	TITLE_FADE = 2,
	TITLE_DONE = 3
};

class Selector;

class Title : public IGameScene
{
public:
	Title(Selector* pSystem);
	virtual ~Title();
	virtual GameSceneResultCode move() override;	// �A�j���[�V�������\�b�h�@GAMESCENE_DEFAULT:�p�� / GAMESCENE_END_OK:�Q�[���J�n
	virtual void draw() override;	// �`�惁�\�b�h

protected:
	Selector* System;
	TitlePhase	Phase;
	bool	Flag;
	INT		Timer;
	INT		FadeTimer;
};

