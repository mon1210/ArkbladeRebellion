// Windowsアプリケーション開発用の共通ヘッダファイル
#include "..\stdafx.h"
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "SceneManager.h"
// 定数値を定めたヘッダファイル
#include "..\Constants.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "..\Title\Title.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "..\Game\Game.h"


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
* @brief ゲーム全体のシーンとPhaseを管理
*/
void SceneManager::manageSceneAndPhase() {
	GameSceneResultCode Rc = GameSceneResultCode::GAMESCENE_DEFAULT;

	switch (GamePhase) {

	case GamePhase::GAMEPHASE_INIT:
		GamePhase = GamePhase::GAMEPHASE_RESET;

	case GamePhase::GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		GamePhase = GamePhase::GAMEPHASE_TITLE;
		
	// タイトルシーン
	case GamePhase::GAMEPHASE_TITLE:
		if (pScene != nullptr)
			Rc = pScene->move();
		if (Rc == GameSceneResultCode::GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Game(this);
		GamePhase = GamePhase::GAMEPHASE_GAME;
		
		// ゲームシーン
	case GamePhase::GAMEPHASE_GAME:
		if (pScene != nullptr)
			Rc = pScene->move();
		if (Rc == GameSceneResultCode::GAMESCENE_DEFAULT)
			break;

		GamePhase = GamePhase::GAMEPHASE_RESET;
	}
}


/**
* @brief ゲーム全体の描画を行う関数
*/
void SceneManager::doDraw() {

	//	シーンを描画
	if (pScene != nullptr)
		pScene->draw();
}


/**
* @brief シーン遷移時のフェードアウト
* @note  Title => Game , Game => Title に使用
*/
void SceneManager::fadeOut(int start_time)
{
	// startTimeはフェードアウトが始まる時間で取得
	float elapsedFrames = (GetNowCount() - start_time) * (FRAME / 1) / 1000;  // 経過フレーム数	 / 1000 => 60(f/s)を実装
	fadeTimer = clampF(elapsedFrames, 0.f, fadeTime);

	// フェードアウト処理
	if (fadeTimer < fadeTime)
	{
		// (fadeTimer / fadeTime) を何回やるかで実行
		float opacity = MAX_OPACITY * (fadeTimer / fadeTime);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(opacity));
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}