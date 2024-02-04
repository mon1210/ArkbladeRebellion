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
	/**
	* @brief Gameのコンストラクタ
	*/
	Game(SceneManager* System_);
	~Game(void);
	/**
	* @brief 管理メソッド
	* @note
	* @return GAMESCENE_DEFAULT: 継続 / GAMESCENE_END_FAILURE: ゲームオーバー
	*/
	GameSceneResultCode move() override;
	/**
	* @brief 描画処理
	* @note  毎フレーム実行される
	*/
	void draw() override;
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
	/**
	* @brief 初期化メソッド
	* @note  別クラスの初期化メソッドを管理
	*/
	void initialize();
	/**
	* @brief 更新メソッド
	* @note  毎フレームの処理
	*		 別クラスの更新メソッドを管理
	*/
	void update();
private:
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

//	マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }