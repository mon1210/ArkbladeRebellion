/**
* @file Title.cpp
* @brief クラス Title の実装
*/

// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// Direct2Dのヘッダファイルをインクルード
#include <d2d1.h>
// DirectWrite ヘッダーファイルをインクルード
#include <dwrite.h>
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"
// テクスチャとビットマップの読み込みと管理に関するクラスとインターフェースを定義
#include "TextureLoader.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


/**
* @brief Titleのコンストラクタ
*/
Title::Title(Selector* pSystem)
{
	ID3D11RenderTargetView* pTarget;

	System = pSystem;	//---Select
	Phase = TITLE_INIT;	//---TitlePhase
	Timer = 0;			//---INT
	FadeTimer = 0;		//---INT
	pImage = NULL;		//---ID2D1Bitmap
	pImage2 = NULL;		//---ID2D1Bitmap
	Black = NULL;		//---ID2D1SolidColorBrush

	//pTarget = pSystem->GetRenderTarget();
	//if (pTarget) {
	//	// 画像をメモリに読み込む
	//	TextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\title_background.png"), &m_pImage);
	//	TextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\title_string.png"), &m_pImage2);
	//	TextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\title_press_space.png"), &m_pImage3);
	//	pTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlack);
	//	pTarget->Release();
	//	pTarget = NULL;
	//}
}


// デストラクタ
Title::~Title()
{
	SAFE_RELEASE(pImage);
	SAFE_RELEASE(pImage2);
	SAFE_RELEASE(pImage3);
	SAFE_RELEASE(Black);
}


/**
* @brief アニメーションメソッド
* @return GAMESCENE_DEFAULT:継続 / GAMESCENE_END_OK:ゲーム開始
*/
GameSceneResultCode Title::move()
{
	switch (Phase) {
		// タイトル開始
	case TITLE_INIT:
		Timer = TITLE_TIMER_INIT;
		Flag = true;
		Phase = TITLE_RUN;

		// タイトル画面
	case TITLE_RUN:
	{	//	これがないと bDone の初期化でエラーがでる
		bool bDone = false;
		Timer++;

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!Flag) {
				bDone = true;
				Flag = true;
			}
		}
		else	// 何もしていない時
		{
			Flag = false;
		}
		// タイトル終了フラグON
		if (bDone) {
			FadeTimer = TITLE_DONE_TIME;
			Phase = TITLE_FADE;
		}
		break;
	}

	// タイトルフェードアウト
	case TITLE_FADE:
		FadeTimer++;
		// 30フレームかけてフェードアウト
		if (FadeTimer < TITLE_FADEOUT_TIME)
			break;
		Phase = TITLE_DONE;

		// タイトル終了
	case TITLE_DONE:
		return GAMESCENE_END_OK;
	}

	return GAMESCENE_DEFAULT;
}


/**
* @brief 描画処理
* @note	 
*/
void Title::draw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget)
{
	printf("Title");

}