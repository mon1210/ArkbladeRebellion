#include "DxLib.h"
#include <vector>
#include "..\Constants.h"
#pragma once

/*	
	辺の長さ1の立方体を作る
	中心点があり、そこから八つの頂点に対して行列をかけることで作るイメージ
	中心点の定義はしない
*/

class OBBCollider
{
public:
	OBBCollider(VECTOR scale_, VECTOR rotate_, VECTOR translate_);	// コンストラクタ　クラスごとに定義することで作成する
	~OBBCollider();

	void changeScaleMatrix(VECTOR& scale_);							// scaleMatrix変更用メソッド
	void changeRotateMatrix(VECTOR& rotate_);						// rotateMatrix変更用メソッド
	void changeTranslateMatrix(VECTOR& translate_);					// translateMatrix変更用メソッド
	void setParentMatrix(MATRIX parent_);							// parentMatrixセット用メソッド
private:
	void update();													// 更新メソッド

#ifdef _DEBUG
public:
	void draw();													// 描画メソッド
#endif // _DEBUG

private:
	// 現在の頂点座標
	VECTOR currentVertices[MAX_VERTICES]{};

	// MGetIdent()　MATRIXクラスのコンストラクタで、変数を初期化している
	MATRIX scaleMatrix	  { MGetIdent() };		// 拡縮行列
	MATRIX rotateMatrix	  { MGetIdent() };		// 回転行列
	MATRIX translateMatrix{ MGetIdent() };		// 平行移動行列
	MATRIX parentMatrix	  { MGetIdent() };		// 親の変換行列

	MATRIX transformMatrix{ MGetIdent() };		// 変換行列　上記の行列をまとめて保存する
};