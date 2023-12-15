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
	~Game(void);
	GameSceneResultCode move() override;	// アニメーション(1フレーム)の実行
	void draw() override;					// 描画メソッド
	ModelManager *GetModelManager();		// Modelを取得して返す
	Collision *GetCollision();				// Collisionを取得して返す
	Radar *GetRadar();						// Radarを取得して返す
	BG	*GetBG();							// BGを取得して返す
	Player *GetPlayer();					// Playerを取得して返す
	Camera *GetCamera();					// Cameraを取得して返す
protected:
	SceneManager *System = NULL;
	Player		 *pPlayer = NULL;
	Enemy		 *pEnemy = NULL;
	ModelManager *pModelManager = NULL;
	Camera		 *pCamera = NULL;
	BG			 *pBG = NULL;
	Grid		 *pGrid = NULL;
	Collision	 *pCollision = NULL;
	Radar		 *pRadar = NULL;
	StagePhase	 Phase = STAGE_INIT;
	bool		 bPause = false;			//	ポーズボタン連打防止フラグ
	int			 Timer = 0;
};