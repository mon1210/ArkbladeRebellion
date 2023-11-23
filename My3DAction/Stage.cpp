// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// Direct2Dのヘッダファイルをインクルード
#include <d2d1.h>
//双方向リスト (Doubly Linked List) データ構造を提供
#include <list>
// ゲームの背景を管理するクラスと関連データを定義
#include "BG.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"
// テクスチャとビットマップの読み込みと管理に関するクラスとインターフェースを定義
#include "TextureLoader.h"
// プレイヤーキャラクターとその関連情報を定義したクラスと定数/列挙型の定義
#include "Player.h"
// 敵キャラクターセットアップと管理に関するクラスとデータの定義
#include "Enemy.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


/**
* @brief Shotのコンストラクタ
*/
Stage::Stage(Selector* pSystem)
{
	ID3D11RenderTargetView* pTarget = NULL;
	ID2D1RenderTarget* pTarget2D = NULL;
	System = pSystem;
	pPlayer = NULL;
	pEnemy = NULL;
	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;

	pTarget = System->GetRenderTarget();
	if (pTarget)
	{
		pPlayer = new Player(this);
		pEnemy = new Enemy(this);

	}
	pTarget2D = System->GetRenderTarget2D();
	if(pTarget2D)
	{
		pBG = new BG(pTarget2D);

	}

	SAFE_RELEASE(pTarget);
	SAFE_RELEASE(pTarget2D);


}


// デストラクタ
Stage::~Stage()
{

	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pBG);

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
void Stage::draw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget)
{
	switch (Phase)
	{
	/* case STAGE_MAPCHANGE_X:
			break;
	   case STAGE_MAPCHANGE_Y:
			break;
	*/
		default:
			if (pBG)
				pBG->draw(pRenderTarget);
			if (pPlayer)
				pPlayer->Update();
			if (pEnemy)
				pEnemy->Update();
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		//float opacity = (float)Timer / STAGE_DONE_TIMER;

		//D2D1_SIZE_F size;
		//size = pRenderTarget->GetSize();

		//D2D1_RECT_F		rc;		// 描画領域(画面上での位置やサイズ)を指定する変数
		//rc.left = 0;	// 描画領域の左上隅指定
		//rc.top = 0;	//			〃
		//rc.right = size.width;		// 描画領域の右下隅指定
		//rc.bottom = size.height;		//			〃
		//m_pBlackBrush->SetOpacity(opacity);
		//pRenderTarget->FillRectangle(rc, m_pBlackBrush);
	}
		break;
	default:
		break;
	}

}