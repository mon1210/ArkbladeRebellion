// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームの背景を管理するクラスと関連データを定義
#include "BG.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


//  マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }


/**
* @brief BGのコンストラクタ
*/
BG::BG()
{
	tile_handle = MV1LoadModel("res\\test_Tile_model.mv1");
	position = VGet(0.f, 0.f, 0.f);

}


// デストラクタ
BG::~BG()
{
}


/**
* @brief 描画メソッド
* @note  画面上に見えている部分のみ描画
*/
void BG::draw() 
{
	// 
	MV1SetPosition(tile_handle, position);
	// 
	MV1DrawModel(tile_handle);

}