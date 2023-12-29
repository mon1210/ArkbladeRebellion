/**
* @file SceneManager.cpp
* @brief クラスSceneManagerの実装ファイル
*/
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
* @brief 全体のアニメートを行う関数
*
*/
void SceneManager::doAnim() {
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
* @brief 全体の描画を行う関数
*/
void SceneManager::doDraw() {

	// 1バイトのビット数(2^8)
	TCHAR	Str[256];

	//	シーンを描画
	if (pScene != nullptr)
		pScene->draw();
}


/**
* @brief シーン遷移時のフェードアウト　Todo 未完成
* @note  Title => Game , Game => Title に使用
*/
void SceneManager::fadeOut()
{
	int c = 0;

	//while (1)
	//{
	//	if (c >= 0 && c < 256)                    　//cが0～256の時
	//		SetDrawBright(c, c, c);					//段々あかるく(c= 0->255)
	//	if (c >= 256 && c < 400)                  　//cが256～400の時
	//		SetDrawBright(255, 255, 255);			//通常の明るさ
	//	if (c >= 400 && c < 400 + 256)              //cが400～400+256の時
	//		SetDrawBright(255 - (c - 400), 255 - (c - 400), 255 - (c - 400));	//段々暗く(c = 255 -> 0)

	//	DrawBox(0, 0, 640, 480, WHITE, TRUE);		//画面全体に白い四角形を描画

	//	c++;										//cをカウントアップ

	//	if (c == 400 + 256) break;                  //暗くなり終わったら終了
	//}


}