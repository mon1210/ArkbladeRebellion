/**
* @file Title.cpp
* @brief クラス Title の実装
*/
// Windowsアプリケーション開発用の共通ヘッダファイル
#include "..\stdafx.h"
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "..\SceneManager\SceneManager.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"


/**
* @brief Titleのコンストラクタ
*/
Title::Title(SceneManager *pSystem)
{
	System = pSystem;
}


// デストラクタ
Title::~Title()
{
}


/**
* @brief  管理メソッド
* @return GAMESCENE_DEFAULT:継続 / GAMESCENE_END_OK:ゲーム開始
*/
GameSceneResultCode Title::move()
{
	switch (Phase) {
		// タイトル開始
	case TitlePhase::TITLE_INIT:
		Phase = TitlePhase::TITLE_RUN;

		// タイトル画面
	case TitlePhase::TITLE_RUN:
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			fadeTimer = TITLE_DONE_TIME;
			Phase = TitlePhase::TITLE_FADE;
		}
		break;
	}

	// タイトルフェードアウト
	case TitlePhase::TITLE_FADE:
		if (fadeTimer++ < TITLE_FADEOUT_TIME)
			break;
		Phase = TitlePhase::TITLE_DONE;

		// タイトル終了
	case TitlePhase::TITLE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;
	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


/**
* @brief 描画処理
*/
void Title::draw()
{
	// Title
	LoadGraphScreen(TITLE_POS_X, TITLE_POS_Y, "res\\test_title_background.png", TRUE);
	// press space
	LoadGraphScreen(TITLE_PS_POS_X, TITLE_PS_POS_Y, "res\\test_title_press_space.png", TRUE);

	switch (Phase) 
	{
	case TitlePhase::TITLE_FADE:
	case TitlePhase::TITLE_DONE:
		if (!isFadeStart) 
		{ 
			startTime = GetNowCount(); 
			isFadeStart = true; 
		}
		System->fadeOut(startTime);
		break;
	}

}