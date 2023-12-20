/*
* @file		ModelManager.h
* @brief	クラス ModelManager の宣言
* @note		モデルに関する処理を管理する
* 
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"


class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	// 以下取得用定数===================================================================== //
	int GetPlayerModel();		// Playerモデルを取得して返すメソッド
	int GetEnemyModel();		// Enemyモデルを取得して返すメソッド
	int GetTileModel();			// Tileモデルを取得して返すメソッド
	// 以上取得用定数===================================================================== //
protected:
	int		playerHandle = 0;	// プレイヤーモデル保存用
	int		enemyHandle = 0;	// エネミーモデル保存用
	int		tileHandle = 0;		// 床モデル保存用
};