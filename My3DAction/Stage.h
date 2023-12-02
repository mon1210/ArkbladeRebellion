/**
* @file		Stage.h
* @brief	クラス Stage の宣言
*/
#pragma once
#include "Selector.h"
#include <list>

//--- ヘッダガードで同じファイルが二度インクルードされることを防いでいる
#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class Player;
class Enemy;
class BG;
class Grid;

enum StagePhase {
	STAGE_INIT = 0,
	STAGE_RUN = 1,
	STAGE_PAUSE = 2,
	STAGE_FADE = 3,
	STAGE_DONE = 4,
};

class Stage : public IGameScene
{
public:
	Stage(Selector* pSystem);
	virtual ~Stage(void);
	virtual GameSceneResultCode move() override;	// アニメーション(1フレーム)の実行
	virtual void draw() override;	// 描画メソッド
protected:
	Selector*	System;
	Player*		pPlayer;
	Enemy*		pEnemy;
	BG*			pBG;
	Grid*		pGrid;
	StagePhase	Phase;
	bool		bPause;		//	ポーズボタン連打防止フラグ
	int		Timer;
};