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
	// 以下取得用定数===================================================================== //
	int GetHandle(ModelType type_);		// モデルを取得して返すメソッド
	// 以上取得用定数===================================================================== //
private:
	void initializeModelList();			// unordered_map初期化メソッド　戻り値になる変数を登録	
protected:
	std::unordered_map<ModelType, int> modelList;	// モデルハンドルの入ったunordered_mapを定義
};