/**
* @file		OBBCollider.h
* @brief	クラス OBBCollider の宣言
*/
#pragma once
#include "DxLib.h"
#include <vector>
#include "..\Axis.h"
#include "..\Constants.h"

/*
	辺の長さ1の立方体を作る
	中心点があり、そこから八つの頂点に対して行列をかけることで作るイメージ
	中心点の定義はしない
*/

class OBBCollider
{
public:
	/**
	* @brief OBBColliderのコンストラクタ
	* @note  引数の値を基に、OBBColliderを作成
	* @param[in] scale			拡縮値
	* @param[in] rotate			回転値
	* @param[in] translate		移動値
	*/
	OBBCollider(VECTOR scale, VECTOR rotate, VECTOR translate);

	// デストラクタ
	~OBBCollider();

	/**
	* @brief scaleMatrix変更用メソッド
	* @param[in] scale	拡縮値
	*/
	void changeScaleMatrix(VECTOR& scale);

	/**
	* @brief rotateMatrix変更用メソッド
	* @param[in] rotate	回転値
	*/
	void changeRotateMatrix(VECTOR& rotate);

	/**
	* @brief translateMatrix変更用メソッド
	* @param[in] translate	移動値
	*/
	void changeTranslateMatrix(VECTOR& translate);

	/**
	* @brief parentMatrixセット用メソッド
	* @param[in] parent	親の変換行列
	*/
	void setParentMatrix(MATRIX parent);

	/**
	* @brief 描画メソッド
	* @param[in] color 描画時の色
	*/
	void draw(unsigned int color);

	// 以下取得用定数===================================================================== //
	/**
	* @brief OBBからローカル軸を取得
	* @note  関数のオーバーロード
	* @param[in,out] axis Axis構造体
	*/
	void GetAxis(Axis& axis);
	/**
	* @brief OBBからローカル軸を取得
	* @param[in,out] x_axis Axis構造体のX成分
	* @param[in,out] y_axis Axis構造体のY成分
	* @param[in,out] z_axis Axis構造体のZ成分
	*/
	void GetAxis(VECTOR& x_axis, VECTOR& y_axis, VECTOR& z_axis);
	// 以上取得用定数===================================================================== //
private:
	/**
	* @brief 更新メソッド
	*/
	void update();

public:
	//! 現在の頂点座標
	VECTOR currentVertices[MAX_VERTICES] = { VGet(0.f, 0.f, 0.f) };

private:
	// MGetIdent()　MATRIXクラスのコンストラクタで、変数を初期化している

	//! 拡縮行列
	MATRIX scaleMatrix = MGetIdent();
	//! 回転行列
	MATRIX rotateMatrix = MGetIdent();
	//! 平行移動行列
	MATRIX translateMatrix = MGetIdent();
	//! 親の変換行列
	MATRIX parentMatrix = MGetIdent();

	//! 変換行列　上記の行列をまとめて保存する
	MATRIX transformMatrix = MGetIdent();
};