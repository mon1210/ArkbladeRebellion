/**
* @file Title.cpp
* @brief クラス Title の実装
*/
// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "SceneManager.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"


/**
* @brief Titleのコンストラクタ
*/
Title::Title(SceneManager *pSystem)
{
	System = pSystem;	//---Select
	Phase = TITLE_INIT;	//---TitlePhase
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
		titleRunFlag = true;
		Phase = TITLE_RUN;

		// タイトル画面
	case TITLE_RUN:
	{	//	これがないと bDone の初期化でエラーがでる
		bool bDone = false;

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!titleRunFlag) {
				bDone = true;
				titleRunFlag = true;
			}
		}
		else	// 何もしていない時
		{
			titleRunFlag = false;
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
	// Title
	LoadGraphScreen(TITLE_POS_X, TITLE_POS_Y, "res\\test_title_background.png", TRUE);
	// press space
	LoadGraphScreen(TITLE_PS_POS_X, TITLE_PS_POS_Y, "res\\test_title_press_space.png", TRUE);

	switch (Phase) 
	{
	case TITLE_FADE:
	case TITLE_DONE:
		System->FadeOut();
	}

}