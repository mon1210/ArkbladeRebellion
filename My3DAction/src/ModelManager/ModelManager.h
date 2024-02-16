/*
* @file		ModelManager.h
* @brief	クラス ModelManager の宣言
* @note		モデルに関する処理を管理する
*/
#pragma once
#include "DxLib.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include <unordered_map>


class ModelManager
{
public:
	/**
	* @brief Modelのコンストラクタ
	*/
	ModelManager();
	~ModelManager();
	// 以下取得用定数===================================================================== //
	/**
	* @brief モデルを取得して返す
	*/
	int GetHandle(ModelType type);
	// 以上取得用定数===================================================================== //
private:
	/**
	* @brief unordered_map初期化メソッド　
	* @note  登録と同時にZBufferも適用する
	*/
	void initializeModelList();
private:
	std::unordered_map<ModelType, int> modelList;	// モデルハンドルの入ったunordered_mapを定義
};