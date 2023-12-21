/*
* @file		ModelManager.h
* @brief	クラス ModelManager の宣言
* @note		モデルに関する処理を管理する
* 
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include <unordered_map>


class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	void initializeModelList();			// unordered_map初期化メソッド　戻り値になる変数を登録	
	// 以下取得用定数===================================================================== //
	int GetHandle(ModelType type_);		// モデルを取得して返すメソッド
	// 以上取得用定数===================================================================== //
protected:
	int		playerHandle = 0;						// プレイヤーモデル保存用
	int		enemyHandle = 0;						// エネミーモデル保存用
	int		tileHandle = 0;							// 床モデル保存用

	std::unordered_map<ModelType, int> modelList;	// モデルハンドルの入ったunordered_mapを定義
};