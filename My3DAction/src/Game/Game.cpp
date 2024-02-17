// Windowsアプリケーション開発用の共通ヘッダファイル
#include "..\stdafx.h"
#include "Game.h"


// コンストラクタ
Game::Game(SceneManager *System)
{
	pSystem = System;

	// インスタンス化
	pModelManager = new ModelManager();
	pCamera = new Camera(this);
	pBG = new BG(this);
	pCollision = new Collision(this);	// 必ずPlayerより上に書く
	pRadar = new Radar();				// 必ずPlayerより上に書く
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pGrid = new Grid();
	pHPBar = new HPBar(this);
	pHealCounter = new HealCounter(this);
}


// 初期化メソッド
void Game::initialize()
{
	if (pPlayer)
		pPlayer->initialize(MAX_HP);
	if (pEnemy)
		pEnemy->initialize(ENEMY_MAX_HP);
	if (pCollision && pBG)
		pCollision->initialize(pBG->GetModelHandle());

}


// 更新メソッド
void Game::update()
{
	if (pPlayer)
		pPlayer->update();
	if (pCamera)
		pCamera->update();
	if (pEnemy)
		pEnemy->update();
	if (pHPBar)
		pHPBar->update();
	if (pHealCounter)
		pHealCounter->update();
}


// デストラクタ
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
	SAFE_DELETE(pHPBar);
	SAFE_DELETE(pHealCounter);
}


// 管理メソッド
GameSceneResultCode Game::move()
{
	switch (stagePhase)
	{
	case StagePhase::STAGE_INIT:
		initialize();
		stagePhase = StagePhase::STAGE_RUN;
		break;

	case StagePhase::STAGE_RUN:
		// --------------------- STAGE_RUN START ------------------- //

		//	ポーズ画面呼び出し
		if (CheckHitKey(KEY_INPUT_P))		// P 
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

		if (pPlayer && pEnemy)
		{
			if (!pPlayer->isAlive() || !pEnemy->isAlive())
			{
				stagePhase = StagePhase::STAGE_FADE;
				timer = 0;
			}
			if (pRadar)
				pRadar->listReset();	// Pointリスト初期化
			
			// 更新
			update();		
		}
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
			}
		}
		else 
		{
			bPause = false;
		}

		break;

	case StagePhase::STAGE_FADE:
		if (timer++ >= STAGE_FADE_TIMER)
		{
			stagePhase = StagePhase::STAGE_DONE;
		}
		break;

	case StagePhase::STAGE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;

	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


// 描画処理
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
	if (pHPBar)
		pHPBar->draw();
	if (pHealCounter)
		pHealCounter->draw();

	// フェードアウト描画用
	switch (stagePhase)
	{
	case StagePhase::STAGE_FADE:
	case StagePhase::STAGE_DONE:
		// フェードアウト処理
		if (!isFadeStart)
		{
			startTime = GetNowCount();
			isFadeStart = true;
		}
		pSystem->fadeOut(startTime);
		break;
	}
}


// ModelManagerを取得して返す
ModelManager *Game::GetModelManager()
{
	if (!pModelManager)
	{
		return nullptr;
	}

	return pModelManager;
}


// Collisionを取得して返す
Collision *Game::GetCollision()
{
	if (!pCollision)
	{
		return nullptr;
	}

	return pCollision;
}


// Radarを取得して返す
Radar *Game::GetRadar()
{
	if (!pRadar)
	{
		return nullptr;
	}

	return pRadar;
}


// BGを取得して返す
BG *Game::GetBG()
{
	if (!pBG)
	{
		return nullptr;
	}

	return pBG;
}


// Playerを取得して返す
Player *Game::GetPlayer()
{
	if (!pPlayer)
	{
		return nullptr;
	}

	return pPlayer;
}


// Cameraを取得して返す
Camera *Game::GetCamera()
{
	if (!pCamera)
	{
		return nullptr;
	}

	return pCamera;
}


// Enemyを取得して返す
Enemy *Game::GetEnemy() 
{
	if (!pEnemy)
	{
		return nullptr;
	}

	return pEnemy;
}