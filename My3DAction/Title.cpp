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



void SceneFadeOut(int TmpValue)
{


	SetDrawScreen(DX_SCREEN_BACK);

	//フェード値の設定（0～255の値が有効）
	TmpValue = 255;		// 変数名変更 Todo

	while(1)
	{
		ClearDrawScreen(); // 裏画面のデータを全て削除

		if (TmpValue < 256) 
		{
			SetDrawBright(TmpValue, TmpValue, TmpValue);
		}

		TmpValue--;

		// 0で終了
		if (TmpValue == 0) 
		{
			break;
		}

		// エラー回避
		if (ProcessMessage() == -1) 
		{
			break;
		}

		ScreenFlip();
	}

}

int tmp = 255;

/**
* @brief 描画処理
* @note	 
*/
void Title::draw()
{
	// Title
	LoadGraphScreen(0, 0, "res\\test_title_background.png", TRUE);
	// press space
	LoadGraphScreen(20, 240, "res\\test_title_press_space.png", TRUE);

	switch (Phase) 
	{
	case TITLE_FADE:
	case TITLE_DONE:
		while (tmp >= 0)
		{
			SceneFadeOut(tmp);
			tmp--;
		}
	}

}