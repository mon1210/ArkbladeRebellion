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
// Direct2Dのヘッダファイルをインクルード
#include <d2d1.h>

#include <d3d11.h>
#include <d2d1_1.h>

// DirectWrite ヘッダーファイルをインクルード
#include <dwrite.h>
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"

#pragma comment(lib,"d2d1.lib")		//	direct2d に必要
#pragma comment(lib,"dwrite.lib")	//	文字表示に必要

#define MAX_LOADSTRING 100

#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if(o){ delete [] (o); o = NULL; }


//!	関数WndProcのプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//!	グローバル変数
ID2D1Factory* g_pD2DFactory = NULL;		//	D2D1Factoryオブジェクト
ID2D1HwndRenderTarget* g_pRenderTarget = NULL;	//	描画ターゲット
ID3D11Device* g_pD3DDevice = NULL;                 // D3D11デバイス
ID3D11DeviceContext* g_pD3DDeviceContext = NULL;   // D3D11デバイスコンテキスト
IDXGISwapChain* g_pSwapChain = NULL;                // スワップチェーン
ID3D11RenderTargetView* g_pRenderTargetView = NULL;// レンダーターゲットビュー


double		g_dblDenominator;
double		g_dblFrame;
__int64		g_i64OldTimer;
#define FPS 60.0
#define INTERVAL (1.0/FPS)

Selector* g_pSelector = NULL;	//	ゲームシステムオブジェクト

/**
* @fn
* @brief	アプリケーションのエントリーポイント
*/
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	   lpCmdLine,
	int	   nCmdShow)
{
	//! デバッグ用のフラグセット
	//--- メモリデバッグを行うために使用される _Crt ライブラリの関数
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//--- COM（Component Object Model）を初期化するための関数
	CoInitialize(NULL);		// ここからCOM使用可

	//! 変数宣言
	WNDCLASSEX wcex;	//	ウィンドウクラス構造体
	HWND	hWnd;		//	ウィンドウハンドル
	RECT	bounds, client;	//	RECT構造体


	/*********************
		1.初期化部分
	*********************/

	//	1-a	ウィンドウクラスの登録
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;	//	ウィンドウプロシージャの登録
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;				//	アプリケーションインスタンス
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + WINDOW_BG_COLOR_OFFSET);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("My3DAction");	//	ウィンドウクラス名
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wcex);


	//	1-b ウィンドウの生成
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wcex.lpszClassName, _T("My3DAction"),
		WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, WINDOW_POS_Y, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;

	// ウィンドウサイズの調整
	GetWindowRect(hWnd, &bounds); // ウィンドウサイズ	:枠を含んだサイズ
	GetClientRect(hWnd, &client); // クライアントサイズ	:枠を含まない表示領域
	MoveWindow(hWnd, bounds.left, bounds.top,
		WINDOW_WIDTH_SIZE * 2 - client.right,		// ウィンドウサイズに枠を足す->クライアントサイズを狙ったサイズにできる
		WINDOW_HEIGHT_SIZE * 2 - client.bottom,
		false);

	// ウィンドウの再表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//	再表示の際、WndProcが呼び出されることに注意！


	//	1-c Direct2Dの初期化 ----------------------------------------------------------------
	//{
	//	HRESULT hr;
	//	//	Direct2D Factory の生成
	//	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	//	GetClientRect(hWnd, &client);
	//	D2D1_SIZE_U size = D2D1::SizeU(
	//		client.right - client.left,
	//		client.bottom - client.top
	//	);

	//	//	Direct2D 描画ターゲット の生成
	//	hr = g_pD2DFactory->CreateHwndRenderTarget(
	//		D2D1::RenderTargetProperties(),
	//		D2D1::HwndRenderTargetProperties(hWnd, size),
	//		&g_pRenderTarget
	//	);
	//}
	

	//	1-c Direct3Dの初期化
	{
		/*
			「バッファ」
			複数の機器やソフトウェアの間でデータをやり取りするときに、
			処理速度や転送速度の差を補うために
			データを一時的に保存しておく記憶装置や記憶領域のこと
		*/
		DXGI_SWAP_CHAIN_DESC scd = {};
		scd.BufferCount = 1;									 // バッファの数
		scd.BufferDesc.Width = WINDOW_WIDTH_SIZE;                // バッファの幅
		scd.BufferDesc.Height = WINDOW_HEIGHT_SIZE;              // バッファの高さ
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;      // バッファのフォーマット
		scd.BufferDesc.RefreshRate.Numerator = 60;               // リフレッシュレートの分子
		scd.BufferDesc.RefreshRate.Denominator = 1;              // リフレッシュレートの分母
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;       // バッファの使用法
		scd.OutputWindow = hWnd;								 // 出力先のウィンドウハンドル
		scd.SampleDesc.Count = 1;                                // マルチサンプリングのサンプル数
		scd.SampleDesc.Quality = 0;                              // マルチサンプリングの品質
		scd.Windowed = TRUE;                                     // ウィンドウモードで起動

		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
		D3D11CreateDeviceAndSwapChain(
			nullptr,                             // デバイスを作成するアダプタ (nullptr ならばデフォルトのアダプタを使用)
			D3D_DRIVER_TYPE_HARDWARE,            // ドライバータイプ
			nullptr,                             // ソフトウェアレンダラーを使用する場合のドライバーモジュール
			0,                                   // フラグ
			featureLevels,                       // サポートするDirect3Dの機能レベルの配列
			_countof(featureLevels),             // 機能レベルの数
			D3D11_SDK_VERSION,                   // SDKのバージョン
			&scd,                                // スワップチェーンの設定
			&g_pSwapChain,                       // 作成されたスワップチェーンを格納する変数へのポインタ
			&g_pD3DDevice,                       // 作成されたデバイスを格納する変数へのポインタ
			nullptr,                             // サポートされる機能レベルを格納する変数へのポインタ
			&g_pD3DDeviceContext                 // 作成されたデバイスコンテキストを格納する変数へのポインタ
		);
		ID3D11Texture2D* backBuffer = nullptr;
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
		g_pD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &g_pRenderTargetView);
		backBuffer->Release();
	}

	//	1-d タイマーの初期化
	::QueryPerformanceCounter((LARGE_INTEGER*)&g_i64OldTimer);
	__int64		i64Tmp;
	::QueryPerformanceFrequency((LARGE_INTEGER*)&i64Tmp);
	g_dblDenominator = DOUBLE_ONE / (double)i64Tmp;
	g_dblFrame = 0.0f;

	//	ゲームシステム初期化
	g_pSelector = new Selector(g_pRenderTargetView);


	/**************************
		2.メッセージループ
	**************************/
	MSG		msg;
	while (true && !CheckHitKey(KEY_INPUT_ESCAPE)) {

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

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {	// PeekMessage() イベントの取り出し
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);		//	ショートカット等の変換
			DispatchMessage(&msg);		//	イベントの配信。WndProc() 呼び出し
		}
		else {

			double	t;
			::QueryPerformanceCounter((LARGE_INTEGER*)&i64Tmp);
			t = (i64Tmp - g_i64OldTimer) * g_dblDenominator;
			g_i64OldTimer = i64Tmp;
			g_dblFrame += t;

			if (g_dblFrame >= INTERVAL) {
				int c = (int)(g_dblFrame / INTERVAL);
				g_dblFrame -= INTERVAL * c;

				if (g_pSelector)
					g_pSelector->doAnim();

				InvalidateRect(hWnd, NULL, false);	//	書き換えの実行
			}
		}
	}



	/**************************
			3.終了処理
	**************************/

	SAFE_DELETE(g_pSelector);
	SAFE_RELEASE(g_pRenderTarget);
	SAFE_RELEASE(g_pD2DFactory);

	SAFE_RELEASE(g_pRenderTargetView);
	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pD3DDeviceContext);
	SAFE_RELEASE(g_pD3DDevice);

	return (int)msg.wParam;
}


/**
* @fn
* @brief	ウィンドウに渡されたイベントのハンドラ
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message) {

	case WM_PAINT:
		if (g_pRenderTargetView) {

			//g_pRenderTarget->BeginDraw();	//	描画開始

			//g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());	// Transform の設定

			//g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkBlue));	//	画面のクリア

			////	この中に描画処理を書く

			//if (g_pSelector)
			//	g_pSelector->doDraw(g_pRenderTargetView);

			////	この中に描画処理を書く

			//g_pRenderTarget->EndDraw();		//	描画終了


			//	この中に描画処理を書く

			if (g_pSelector)
				g_pSelector->doDraw(g_pRenderTargetView, g_pRenderTarget);

			//	この中に描画処理を書く

			// バックバッファの内容を表示
			g_pSwapChain->Present(0, 0);

		}
		ValidateRect(hWnd, NULL);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}