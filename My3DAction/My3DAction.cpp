/**
* @file		My3DAction.cpp
* @author	R.Monda
* @date		..2023
* @brief	シーン管理クラス		: Selector	(Selector.h)
*			ゲームシーンクラス		: Stage		(Stage.h)
*			プレイヤークラス		: Player	(Player.h)
*			背景・マップクラス		: BG		(BG.h)
* @note		エラーが出た際は、プロジェクトのプロパティを開き、
*			C/C++	 -> 全般 -> 追加のインクルードディレクトリで'Lib;%(AdditionalIncludeDirectories)'を追加する 又は
*			リンカー -> 全般 -> 追加のライブラリディレクトリで'Lib;%(AdditionalIncludeDirectories)'を追加する 又は
*			リンカー -> 入力 -> 追加の依存ファイルで'd3d11.lib'を追加してください
*/

// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// CRT デバッグヘッダファイルをインクルード
#include <crtdbg.h>
// TCHAR タイプやマクロを定義したヘッダファイルをインクルード
#include <tchar.h>
// 標準入出力関数を提供する C ライブラリヘッダファイルをインクルード
#include <stdio.h>
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
// 
#include "BG.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


#define MAX_LOADSTRING 100

#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if(o){ delete [] (o); o = NULL; }

#define FPS 60.0
#define INTERVAL (1.0/FPS)

Selector* g_pSelector = NULL;	//	ゲームシステムオブジェクト
BG* g_BG = NULL;

/**
* @fn
* @brief	アプリケーションのエントリーポイント
*/
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	//! デバッグ用のフラグセット
	//--- メモリデバッグを行うために使用される _Crt ライブラリの関数
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ChangeWindowMode(TRUE);     // ウィンドウモードに設定
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_COLOR);    // ウィンドウ設定

	/*********************
		1.初期化部分
	*********************/

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);	// 描画対象を裏のキャンバスに指定

	// カメラの描画距離   SetCameraNearFar(最短距離,最長距離)
	SetCameraNearFar(0.f, 1000.f);

	//	ゲームシステム初期化
	g_pSelector = new Selector();

	g_BG = new BG();

	// Tileに当たり判定付与
	int tile_handle = g_BG->GetModelHandle();
	MV1SetupCollInfo(
		tile_handle,		// 当たり判定を設定するモデルのハンドル
		-1,					// 対象となるモデルのフレーム番号(-1は全て)	
		32,					// X軸の空間分割数
		32,					// Y軸の空間分割数
		32					// Z軸の空間分割数
	);

	/**************************
		2.メッセージループ
	**************************/
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

		// 背景の色変更　黒色
		SetBackgroundColor(0, 0, 0);

		// クリア関数
		ClearDrawScreen();

		//	この中に描画処理を書く

		if (g_pSelector)
			g_pSelector->doAnim();

		if (g_pSelector)
			g_pSelector->doDraw();

		//	この中に描画処理を書く

		// フリップ関数
		ScreenFlip();

	}

	/**************************
			3.終了処理
	**************************/

	SAFE_DELETE(g_pSelector);
	SAFE_DELETE(g_BG);

	// DXライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}
