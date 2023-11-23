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
#include <stdio.h>\
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
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

	//// インスタンス作成
	//Model modelObject;
	//// モデルセットメソッド呼び出し
	//modelObject.ModelSet();

	//	ゲームシステム初期化
	g_pSelector = new Selector();


	/**************************
		2.メッセージループ
	**************************/
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

		//// カメラの描画位置と見る位置を指定
		SetCameraPositionAndTargetAndUpVec(
			VGet(0.f, 0.f, 0.f),    // カメラ座標
			VGet(0.f, 0.f, 1.f),    // カメラの見る位置
			VGet(0.f, 1.f, 0.f)     // 固定
		);
		// カメラの位置と向きを設定     遠くから
		//SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 1200.0f, -2000.0f), VGet(0.0f, 400.0f, 0.0f));

		// 背景の色変更　灰色
		SetBackgroundColor(128, 128, 128);

		ClearDrawScreen();


		if (g_pSelector)
			g_pSelector->doAnim();

		//	この中に描画処理を書く

		if (g_pSelector)
			g_pSelector->doDraw();

		//	この中に描画処理を書く
		
		//ClearDrawScreen();

		// フリップ関数
		ScreenFlip();

	}

	/**************************
			3.終了処理
	**************************/

	SAFE_DELETE(g_pSelector);

	// DXライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}
