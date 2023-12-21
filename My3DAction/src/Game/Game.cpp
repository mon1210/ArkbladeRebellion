// Windowsアプリケーション開発用の共通ヘッダファイル
#include "..\stdafx.h"
#include "Game.h"


/**
* @brief Gameのコンストラクタ
*/
Game::Game(SceneManager* System_)
{
	pSystem = System_;

	// インスタンス化
	pModelManager = new ModelManager();
	pCamera = new Camera(this);
	pCollision = new Collision(this);	// 必ずPlayerより上に書く
	pRadar = new Radar();				// 必ずPlayerより上に書く
	pBG = new BG(this);
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pGrid = new Grid();
	pUI = new UI(this);
}


/**
* @brief デストラクタ
* @note	 すべてのポインタをここでDelete
*/
Game::~Game()
{
	SAFE_DELETE(pCollision);
	SAFE_DELETE(pGrid);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModelManager);
	SAFE_DELETE(pRadar);
	SAFE_DELETE(pUI);
}


/**
* @brief アニメーション(1フレーム)の実行
* @note 
* @return GAMESCENE_DEFAULT: 継続 / GAMESCENE_END_FAILURE: ゲームオーバー
*/
GameSceneResultCode Game::move()
{
	switch (stagePhase)
	{
	case StagePhase::STAGE_INIT:
		if (pCollision)
			pCollision->initCollision(pBG->GetModelHandle());
		if (pEnemy)
			pEnemy->initAnimation();	// phase分けはEnemyのみなので
		stagePhase = StagePhase::STAGE_RUN;
		break;

	case StagePhase::STAGE_RUN:
		// --------------------- STAGE_RUN START ------------------- //

		//	ポーズ画面呼び出し
		if (GetAsyncKeyState(0x50))		// P 
		{
			if (!bPause) 
			{
				stagePhase = StagePhase::STAGE_PAUSE;
				bPause = true;
			}
		}
		else 
		{
			bPause = false;
		}

		if (pPlayer)
		{
			if (!pPlayer->isAlive())
			{
				stagePhase = StagePhase::STAGE_FADE;
				timer = 0;
			}
			if (pRadar)
				pRadar->listReset();	// Pointリスト初期化
			pPlayer->update();
			if (pCamera)
				pCamera->update();
			if (pEnemy)
				pEnemy->update();
		}

		if (pUI)
			pUI->move();

		break;
		// --------------------- STAGE_RUN END --------------------- //

	case StagePhase::STAGE_PAUSE:
		//	ポーズ画面呼び出し
		if (GetAsyncKeyState(KEY_INPUT_P))	
		{
			if (!bPause) 
			{
				stagePhase = StagePhase::STAGE_RUN;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		break;

	case StagePhase::STAGE_FADE:
		if (timer++ < STAGE_FADE_TIMER)
		{
			break;
		}
		stagePhase = StagePhase::STAGE_DONE;
		break;

	case StagePhase::STAGE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;

	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


/**
* @brief 描画処理
* @note  毎フレーム実行される
*/
void Game::draw()
{
	if (pBG)
		pBG->draw();
	if (pGrid)
		pGrid->draw();
	if (pPlayer)
		pPlayer->draw();
	if (pEnemy)
		pEnemy->draw();
	if (pRadar)
		pRadar->draw();
	if (pUI)
		pUI->draw();

	// フェードアウト描画用
	switch (stagePhase)
	{
	case StagePhase::STAGE_FADE:
	case StagePhase::STAGE_DONE:
	{
		// フェードアウト処理
		pSystem->fadeOut();
	}
		break;
	default:
		break;
	}

}


/**
* @brief ModelManagerを取得して返す
*/
ModelManager* Game::GetModelManager()
{
	return pModelManager;
}


/**
* @brief Collisionを取得して返す
*/
Collision *Game::GetCollision()
{
	return pCollision;
}


/**
* @brief Radarを取得して返す
*/
Radar *Game::GetRadar()
{
	return pRadar;
}


/**
* @brief BGを取得して返す
*/
BG *Game::GetBG()
{
	return pBG;
}


/**
* @brief Playerを取得して返す
*/
Player *Game::GetPlayer()
{
	return pPlayer;
}


/**
* @brief Cameraを取得して返す
*/
Camera *Game::GetCamera()
{
	return pCamera;
}


/**
* @brief Enemyを取得して返す
*/
Enemy* Game::GetEnemy() 
{
	return pEnemy;
}