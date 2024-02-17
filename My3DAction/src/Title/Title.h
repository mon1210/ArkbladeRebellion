/**
* @file		Title.h
* @brief	クラス Title の宣言
*/
#pragma once
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\IGameScene\IGameScene.h"

//! クラスの前方宣言
class SceneManager;

class Title : public IGameScene
{
public:
	/**
	* @brief Titleのコンストラクタ
	*/
	Title(SceneManager *System);

	/**
	* @brief Titleのデストラクタ
	*/
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
	//! 状態を表す
	TitlePhase	Phase = TitlePhase::TITLE_INIT;
	//! FadeOut開始時間取得用
	int		startTime = 0;
	//! FadeOut経過時間
	int		fadeTimer = 0;
	//! FadeOutが開始したかどうかのflag
	bool	isFadeStart = false;
};

