/**
* @file		SceneManager.h
* @brief	クラス SceneManager の宣言
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

	/**
	* @brief SceneManagerのデストラクタ
	*/
	~SceneManager();

	/**
	* @brief ゲーム全体のシーンとPhaseを管理
	*/
	void manageSceneAndPhase();

	/**
	* @brief ゲーム全体の描画を行う関数
	*/
	void doDraw();

	/**
	* @brief シーン遷移時のフェードアウト
	* @note  Title => Game , Game => Title に使用
	* @param[in] start_time フェードアウト開始時間
	*/
	void fadeOut(int start_time);
private:
	//! シーン
	IGameScene *pScene = nullptr;
	//! 状態変数
	GamePhase GamePhase = GamePhase::GAMEPHASE_INIT;
	//! FadeOut開始時間取得用
	int	  startTime = 0;
	//! フェードタイマー
	float fadeTimer = 0.f;
	//! フェード時間（フレーム
	float fadeTime = 60.f;
};

