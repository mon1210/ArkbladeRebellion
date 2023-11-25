// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームの背景を管理するクラスと関連データを定義
#include "BG.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"
// プレイヤーキャラクターとその関連情報を定義したクラスと定数/列挙型の定義
#include "Player.h"
// 敵キャラクターセットアップと管理に関するクラスとデータの定義
#include "Enemy.h"
// 
#include "Grid.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


/**
* @brief Shotのコンストラクタ
*/
Stage::Stage(Selector* pSystem)
{
	System = pSystem;
	pPlayer = NULL;
	pEnemy = NULL;
	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;

	pPlayer = new Player();
	pEnemy = new Enemy();
	pBG = new BG();
	pGrid = new Grid();
}


// デストラクタ
Stage::~Stage()
{

	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pGrid);

}


/**
* @brief アニメーション(1フレーム)の実行
* @note 処理の順番は オブジェクトを move してから各々 collide を取って、必要なら各座標を調整する
* @return GAMESCENE_DEFAULT: 継続 / GAMESCENE_END_FAILURE: ゲームオーバー
*/
GameSceneResultCode Stage::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
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
* @note  現在のマップと次のマップを動かしながら描画することで移動しているように見せる
*/
void Stage::draw()
{
	switch (Phase)
	{
		default:
			if (pBG)
				pBG->draw();
			if (pGrid)
				pGrid->Draw();
			if (pPlayer)
				pPlayer->draw();
			if (pEnemy)
				pEnemy->draw();
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		// フェードアウト処理
	}
		break;
	default:
		break;
	}

}