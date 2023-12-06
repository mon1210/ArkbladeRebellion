/**
* @file Selector.cpp
* @brief クラスSelectorの実装ファイル
*/
// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"


/**
* @brief Selectorのコンストラクタ
*/
Selector::Selector()
{
	// メンバ初期化
	count = 0;
	//wait = 0;
	eGamePhase = GAMEPHASE_INIT;
	pScene = NULL;
}


// デストラクタ
Selector::~Selector()
{
	SAFE_DELETE(pScene);
}


/**
* @brief 全体のアニメートを行う関数
*
*/
void Selector::doAnim() {
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {

	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		eGamePhase = GAMEPHASE_TITLE;	// GAMEへDebug
		
	// タイトルシーン
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Stage(this);
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
	// デバッグ用カウンタ
	count++;
}


/**
* @brief 全体の描画を行う関数
*/
void Selector::doDraw() {

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

