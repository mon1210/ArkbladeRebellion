/**
* @file Title.h
* @brief ÉNÉâÉX CTitle ÇÃêÈåæ
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
struct ID2D1Bitmap;
struct ID2D1SolidColorBrush;

class Title : public IGameScene
{
public:
	Title(Selector* pSystem);
	virtual ~Title();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget) override;

protected:
	Selector* System;
	TitlePhase	Phase;
	ID2D1Bitmap* pImage, * pImage2, * pImage3;
	ID2D1SolidColorBrush* Black;
	bool	Flag;
	INT		Timer;
	INT		FadeTimer;
};

