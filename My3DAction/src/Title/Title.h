/**
* @file		Title.h
* @brief	クラス Title の宣言
*/
#pragma once
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\IGameScene\IGameScene.h"

// クラスの前方宣言
class SceneManager;

class Title : public IGameScene
{
public:
	/**
	* @brief Titleのコンストラクタ
	*/
	Title(SceneManager *System);
	~Title();

	/**
	* @brief  管理メソッド
	* @return GAMESCENE_DEFAULT:継続 / GAMESCENE_END_OK:ゲーム開始
	*/
	GameSceneResultCode move() override;

	/**
	* @brief 描画処理
	*/
	void draw() override;
private:
	SceneManager *pSystem = nullptr;
	TitlePhase	Phase = TitlePhase::TITLE_INIT;		// 状態を表す
	int		startTime = 0;							// FadeOut開始時間取得用
	int		fadeTimer = 0;
	bool	isFadeStart = false;					// FadeOutが開始したかどうかのflag
};

