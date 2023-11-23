// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// Direct2Dのヘッダファイルをインクルード
#include <d2d1.h>
// ゲームの背景を管理するクラスと関連データを定義
#include "BG.h"
// テクスチャとビットマップの読み込みと管理に関するクラスとインターフェースを定義
#include "TextureLoader.h"
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
BG::BG(ID2D1RenderTarget * pRenderTarget)
{

	TextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Title_background.png"), &BGImage);

}


// 
BG::~BG()
{

	SAFE_DELETE(BGImage);

}


/**
* @brief 描画メソッド
* @note  画面上に見えている部分のみ描画
*/
void BG::draw(ID2D1RenderTarget* pRenderTarget) 
{

	// 以下背景描画処理 ============================================
	//D2D1_SIZE_F size;
	D2D1_RECT_F rc,		// 描画領域(画面上での位置やサイズ)を指定する変数
				src;	// テクスチャの中での座標を指定し、テクスチャを決定する変数
	//size = pRenderTarget->GetSize();
	// 描画領域の設定
	rc.left = 0.f; rc.top = 0.f;	// 描画領域の左上隅指定
	rc.right = WINDOW_WIDTH_SIZE; rc.bottom = WINDOW_HEIGHT_SIZE;		// 描画領域の右下隅指定

	// テクスチャ座標の計算
	src.left = 0.f; src.top = 0.f;		// テクスチャ座標の左上隅指定
	src.right = src.left + WINDOW_WIDTH_SIZE; src.bottom = WINDOW_HEIGHT_SIZE;	// テクスチャ座標の右下隅指定

	// 背景の描画
	pRenderTarget->DrawBitmap(BGImage, rc, BG_SCALE_FACTOR, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
	 
	// 以上背景描画処理 ============================================



}