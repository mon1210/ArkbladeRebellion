/**
* @file		Game.h
* @brief	クラス Game の宣言
*/
#pragma once
#include "..\SceneManager\SceneManager.h"
#include "..\BG\BG.h"
#include "..\Player\Player.h"
#include "..\Enemy\Enemy.h"
#include "..\Enums.h"
#include "..\Camera\Camera.h"
#include "..\ModelManager\ModelManager.h"
#include "..\Grid\Grid.h"
#include "..\Collision\Collision.h"
#include "..\Radar\Radar.h"
#include "..\HPBar\HPBar.h"
#include "..\HealCounter\HealCounter.h"
#include "..\Constants.h"

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
class HPBar;
class HealCounter;


class Game : public IGameScene
{
public:
	Game(SceneManager* System_);
	~Game(void);
	GameSceneResultCode move() override;	// 管理メソッド
	void draw() override;					// 描画メソッド
	// 以下取得用定数=================================================== //
	Player			*GetPlayer();			// Playerを取得して返す
	Enemy			*GetEnemy();			// Enemyを取得して返す
	ModelManager	*GetModelManager();		// Modelを取得して返す
	Camera			*GetCamera();			// Cameraを取得して返す
	BG				*GetBG();				// BGを取得して返す
	Collision		*GetCollision();		// Collisionを取得して返す
	Radar			*GetRadar();			// Radarを取得して返す
	// 以上取得用定数=================================================== //
private:
	void initialize();						// 初期化メソッド
	void update();							// 更新メソッド
protected:
	SceneManager *pSystem = nullptr;
	Player		 *pPlayer = nullptr;
	Enemy		 *pEnemy = nullptr;
	ModelManager *pModelManager = nullptr;
	Camera		 *pCamera = nullptr;
	BG			 *pBG = nullptr;
	Grid		 *pGrid = nullptr;
	Collision	 *pCollision = nullptr;
	Radar		 *pRadar = nullptr;
	HPBar		 *pHPBar = nullptr;
	HealCounter  *pHealCounter = nullptr;
	StagePhase	 stagePhase = StagePhase::STAGE_INIT;	// 状態を表す
	int			 timer = 0;
	int			 startTime = 0;							// FadeOut開始時間取得用
	bool		 bPause = false;						// ポーズボタン連打防止フラグ
	bool		 isFadeStart = false;					// FadeOutが開始したかどうかのflag
};