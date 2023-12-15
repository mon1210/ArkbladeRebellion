/**
* @file SceneManager.cpp
* @brief クラスSceneManagerの実装ファイル
*/
// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "SceneManager.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Game.h"


/**
* @brief SceneManagerのコンストラクタ
*/
SceneManager::SceneManager()
{
	startTime = GetNowCount();
}


// デストラクタ
SceneManager::~SceneManager()
{
	SAFE_DELETE(pScene);
}


/**
* @brief 全体のアニメートを行う関数
*
*/
void SceneManager::doAnim() {
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {

	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		eGamePhase = GAMEPHASE_TITLE;
		
	// タイトルシーン
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Game(this);
		eGamePhase = GAMEPHASE_GAME;
		
		// ゲームシーン
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			rc = pScene->move();
		else // pScene == NULL
		{
			printf("");		// Debug
		}
		if (rc == GAMESCENE_DEFAULT)
			break;

		eGamePhase = GAMEPHASE_RESET;
	}
}


/**
* @brief 全体の描画を行う関数
*/
void SceneManager::doDraw() {

	// 1バイトのビット数(2^8)
	TCHAR	str[256];

	//	シーンを描画
	if (pScene != NULL)
		pScene->draw();
	else // pScene == NULL
	{
		printf("");		// Debug
	}
}


/**
* @brief シーン遷移時のフェードアウト　Todo 未完成
* @note  Title => Game , Game => Title に使用
*/
void SceneManager::FadeOut()
{
	int elapsedFrames = (GetNowCount() - startTime) * FRAME / 1000;  // 経過フレーム数	 / 1000 => 60(f/s)を実装
	fadeTimer = Clamp(elapsedFrames, 0, fadeTime);

	// フェードアウト処理
	if (fadeTimer < fadeTime)
	{
		int opacity = MAX_OPACITY * (fadeTimer / fadeTime);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	return;

}