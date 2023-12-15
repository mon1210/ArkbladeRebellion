/**
* @file		Game.h
* @brief	クラス Game の宣言
*/
#pragma once
#include "SceneManager.h"
#include "BG.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "ModelManager.h"
#include "Grid.h"
#include "Collision.h"
#include "Radar.h"
#include "Constants.h"

// クラスの前方宣言
class SceneManager;
class Player;
class Enemy;
class ModelManager;
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

class Game : public IGameScene
{
public:
	Game(SceneManager* pSystem);
	virtual ~Game(void);
	virtual GameSceneResultCode move() override;	// アニメーション(1フレーム)の実行
	virtual void draw() override;					// 描画メソッド
	virtual ModelManager *GetModelManager();		// 
	virtual Collision *GetCollision();				// 当たり判定用のCollisionを返す
	virtual Radar *GetRadar();						// 当たり判定用のRadarを返す
	virtual BG	*GetBG();							// 
protected:
	SceneManager *System;
	Player		 *pPlayer;
	Enemy		 *pEnemy;
	ModelManager *pModelManager;
	Camera		 *pCamera;
	BG			 *pBG;
	Grid		 *pGrid;
	Collision	 *pCollision;
	Radar		 *pRadar;
	StagePhase	 Phase;
	bool		 bPause;		//	ポーズボタン連打防止フラグ
	int			 Timer;
};