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
#include "..\DrawDebugKey\DrawDebugKey.h"
#include "..\ModelManager\ModelManager.h"
#include "..\Collision\Collision.h"
#include "..\Radar\Radar.h"
#include "..\HPBar\HPBar.h"
#include "..\HealCounter\HealCounter.h"
#include "..\Constants.h"

//! クラスの前方宣言
class SceneManager;
class Player;
class Enemy;
class ModelManager;
class Camera;
class DrawDebugKey;
class BG;
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
	Game(SceneManager *System);

	/**
	* @brief Gameのデストラクタ
	*/
	~Game();

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
	/**
	* @brief Playerを取得して返す
	*/
	Player *GetPlayer();

	/**
	* @brief Enemyを取得して返す
	*/
	Enemy *GetEnemy();

	/**
	* @brief Modelを取得して返す
	*/
	ModelManager *GetModelManager();

	/**
	* @brief Cameraを取得して返す
	*/
	Camera *GetCamera();

	/**
	* @brief BGのモデルを取得して返す
	*/
	int GetBGModel();

	/**
	* @brief Collisionを取得して返す
	*/
	Collision *GetCollision();

	/**
	* @brief Radarを取得して返す
	*/
	Radar *GetRadar();
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
	DrawDebugKey *pDrawDebugKey = nullptr;
	BG			 *pBG = nullptr;
	Collision	 *pCollision = nullptr;
	Radar		 *pRadar = nullptr;
	HPBar		 *pHPBar = nullptr;
	HealCounter  *pHealCounter = nullptr;
	//! 状態を表す
	StagePhase	 stagePhase = StagePhase::STAGE_INIT;
	int			 timer = 0;
	//! FadeOut開始時間取得用
	int			 startTime = 0;
	//! FadeOutが開始したかどうかのflag
	bool		 isFadeStart = false;
};

//	以下 マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
/**
* @def SAFE_RELEASE
* @brief ポインタの解放
*/
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
/**
* @def SAFE_DELETE
* @brief ポインタの削除
*/
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
/**
* @def SAFE_DELETE_ARRAY
* @brief ポインタ配列の削除
*/
#define SAFE_DELETE_ARRAY(o) if(o){ delete [] (o); o = NULL; }