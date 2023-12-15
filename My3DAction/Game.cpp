// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
#include "Game.h"


/**
* @brief Gameのコンストラクタ
*/
Game::Game(SceneManager* pSystem)
{
	System = pSystem;
	pModelManager = NULL;
	pCamera = NULL;
	pCollision = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;
	pRadar = NULL;

	Phase = STAGE_INIT;

	bPause = true;

	Timer = 0;

	// インスタンス化
	pModelManager = new ModelManager();
	pCamera = new Camera();
	pCollision = new Collision(this);	// 必ずPlayerより上に書く
	pRadar = new Radar();				// 必ずPlayerより上に書く
	pBG = new BG(this);
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pGrid = new Grid();
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
}


/**
* @brief アニメーション(1フレーム)の実行
* @note 
* @return GAMESCENE_DEFAULT: 継続 / GAMESCENE_END_FAILURE: ゲームオーバー
*/
GameSceneResultCode Game::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
		pCollision->initCollision(pBG->getModelHandle());
		pEnemy->initAnimation();	// phase分けはEnemyのみなので
		Phase = STAGE_RUN;
		break;

	case STAGE_RUN:
		//	ポーズ画面呼び出し
		if (GetAsyncKeyState(0x50))		 // P 
		{
			if (!bPause) 
			{
				Phase = STAGE_PAUSE;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		if (pPlayer)
		{
			if (!pPlayer->move())
			{
				Phase = STAGE_FADE;
				Timer = 0;
				break;
			}
			pPlayer->update();
			if (pRadar)
				pRadar->listReset();	// Pointリスト初期化
			if (pCamera) {
				pCamera->controller();
				pCamera->setPositionAndDirection(pPlayer->getPos());			//カメラの位置・角度設定 
				pPlayer->setCameraHAngle(pCamera->getHorizontalAngle());		// カメラの水平角度取得
				pPlayer->setPlayerNewPos(pCamera->moveAlongHAngle
				(pPlayer->getPlayerMoveVec(), pPlayer->getPos()));	// プレイヤーの座標設定
			}
			if (pEnemy) {
				pEnemy->update();
				pEnemy->setPlayerPos(pPlayer->getPos());
			}

		}
		break;
		// --------------------- STAGE_RUN END --------------------- //

	case STAGE_PAUSE:
		//	ポーズ画面呼び出し
		if (GetAsyncKeyState(0x50))		// P
		{
			if (!bPause) 
			{
				Phase = STAGE_RUN;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		break;

	case STAGE_FADE:
		if (Timer++ < STAGE_FADE_TIMER)
		{
			break;
		}
		Phase = STAGE_DONE;
		break;

	case STAGE_DONE:
		return GAMESCENE_END_OK;

	}

	return GAMESCENE_DEFAULT;
}


/**
* @brief 描画処理
* @note  毎フレーム実行される
*/
void Game::draw()
{
	switch (Phase)
	{
		default:
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
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	// フェードアウト描画用
	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		// フェードアウト処理
		System->FadeOut();
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
BG* Game::GetBG()
{
	return pBG;
}