/**
* @file		SceneManager.h
* @brief	クラスSceneManagerの宣言ファイル
*/
#pragma once
#include "..\IGameScene\IGameScene.h"
#include "..\Enums.h"
#include "..\GlobalFunctions\GlobalFunctions.h"

class IGameScene;	// シーン管理クラス

class SceneManager
{
public:
	/**
	* @brief SceneManagerのコンストラクタ
	*/
	SceneManager();

	// デストラクタ
	~SceneManager(void);

	/**
	* @brief ゲーム全体のシーンとPhaseをswitchで管理
	*/
	void switchSceneAndPhase();

	/**
	* @brief ゲーム全体の描画を行う関数
	*/
	void doDraw();

	/**
	* @brief シーン遷移時のフェードアウト
	* @note  Title => Game , Game => Title に使用
	*/
	void fadeOut(int startTime_);
private:
	IGameScene *pScene = nullptr;						// シーン
	GamePhase GamePhase = GamePhase::GAMEPHASE_INIT;	// 状態変数
	int	  startTime = 0;								// FadeOut開始時間取得用
	float fadeTimer = 0.f;								// フェードタイマー
	float fadeTime = 60.f;								// フェード時間（フレーム）
};

//	マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

