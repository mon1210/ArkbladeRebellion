/**
* @file Title.cpp
* @brief クラス Title の実装
*/
// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


/**
* @brief Titleのコンストラクタ
*/
Title::Title(Selector *pSystem)
{
	System = pSystem;	//---Select
	Phase = TITLE_INIT;	//---TitlePhase
	Timer = 0;			//---INT
	FadeTimer = 0;		//---INT
}


// デストラクタ
Title::~Title()
{
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
void Title::draw()
{

}