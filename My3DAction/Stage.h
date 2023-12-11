/**
* @file		Stage.h
* @brief	クラス Stage の宣言
*/
#pragma once
#include "SceneManager.h"
#include "BG.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Model.h"
#include "Grid.h"
#include "Collision.h"
#include "Radar.h"
#include "Constants.h"
#include "IGameObject.h"

// クラスの前方宣言
class SceneManager;
class Player;
class Enemy;
class Model;
class Camera;
class BG;
class Grid;
class Collision;
class Radar;

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
	Stage(SceneManager* pSystem);
	virtual ~Stage(void);
	virtual GameSceneResultCode move() override;	// アニメーション(1フレーム)の実行
	virtual void draw() override;		// 描画メソッド
	virtual Collision *GetCollision();	// 当たり判定用のCollisionを返す
	virtual Radar *GetRadar();			// 当たり判定用のRadarを返す
protected:
	SceneManager*System;
	Player		*pPlayer;
	Enemy		*pEnemy;
	Model		*pModel;
	Camera		*pCamera;
	BG			*pBG;
	Grid		*pGrid;
	Collision	*pCollision;
	Radar		*pRadar;
	StagePhase	Phase;
	bool		bPause;		//	ポーズボタン連打防止フラグ
	int			Timer;
	int			tileHandle;
};