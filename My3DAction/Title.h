/**
* @file		Title.h
* @brief	クラス Title の宣言
*/
#pragma once
#include "Constants.h"
#include "IGameScene.h"

enum TitlePhase {
	TITLE_INIT = 0,
	TITLE_RUN = 1,
	TITLE_FADE = 2,
	TITLE_DONE = 3
};

// クラスの前方宣言
class SceneManager;

class Title : public IGameScene
{
public:
	Title(SceneManager *pSystem);
	virtual ~Title();
	virtual GameSceneResultCode move() override;	// アニメーションメソッド　GAMESCENE_DEFAULT:継続 / GAMESCENE_END_OK:ゲーム開始
	virtual void draw() override;					// 描画メソッド

protected:
	SceneManager *System = NULL;
	TitlePhase	Phase = TITLE_INIT;
	bool	titleRunFlag = false;					// Titleの状態を管理するflag
	INT		FadeTimer = 0;
};

