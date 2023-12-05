/**
* @file		Stage.h
* @brief	クラス Stage の宣言
*/
#pragma once
#include "Selector.h"
#include "IGameObject.h"

class Selector;
class Player;
class Enemy;
class Model;
class Camera;
class BG;
class Grid;
class Collider;

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
	Stage(Selector *pSystem);
	virtual ~Stage(void);
	virtual GameSceneResultCode move() override;	// アニメーション(1フレーム)の実行
	virtual void draw() override;	// 描画メソッド
	virtual Collider *GetCollider();
protected:
	Selector	*System;
	Player		*pPlayer;
	Enemy		*pEnemy;
	Model		*pModel;
	Camera		*pCamera;
	BG			*pBG;
	Grid		*pGrid;
	Collider	*pCollider;
	StagePhase	Phase;
	bool		bPause;		//	ポーズボタン連打防止フラグ
	int			Timer;
	int			tileHandle;
};