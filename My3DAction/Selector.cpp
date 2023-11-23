/**
* @brief 全体のアニメートを行う関数
*
*/
// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// Direct2Dのヘッダファイルをインクルード
#include <d2d1.h>
// DirectWrite ヘッダーファイルをインクルード
#include <dwrite.h>
// ゲームシーンとセレクターの管理に関連するヘッダファイル
#include "Selector.h"
// タイトル画面のゲームシーンを管理するヘッダファイル
#include "Title.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"
// テクスチャとビットマップの読み込みと管理に関するクラスとインターフェースを定義
#include "TextureLoader.h"


/**
* @brief Selectorのコンストラクタ
*/
Selector::Selector(ID3D11RenderTargetView* pRenderTargetView)
{
	RenderTargetView = pRenderTargetView;
	RenderTargetView->AddRef();

	// メンバ初期化
	count = 0;
	//wait = 0;
	eGamePhase = GAMEPHASE_INIT;
	pScene = NULL;
	//WhiteBrush = NULL;

	// Direct Write 初期化
	{
		HRESULT hr;
		IDWriteFactory* pFactory;
		 // DirectWriteファクトリー生成
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pFactory),
			reinterpret_cast<IUnknown**>(&pFactory)
		);
		 // テキストフォーマット生成
		hr = pFactory->CreateTextFormat(
			L"consolas",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20,
			L"",
			&TextFormat
		);

		SAFE_RELEASE(pFactory);
	}

	// テキスト用ブラシの生成
	//if (FAILED(RenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::White),
	//	&WhiteBrush
	//))) {
	//	SAFE_RELEASE(WhiteBrush);
	//}
}


// デストラクタ
Selector::~Selector()
{
	SAFE_DELETE(pScene);
	//SAFE_RELEASE(WhiteBrush);
	//SAFE_RELEASE(RenderTarget);
	SAFE_RELEASE(Device);
	SAFE_RELEASE(Context);
	SAFE_RELEASE(TextFormat);
	SAFE_RELEASE(RenderTargetView);
	TextureLoader::Destroy();
}


/**
* @brief 全体のアニメートを行う関数
*
*/
void Selector::doAnim() {
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (eGamePhase) {

	case GAMEPHASE_INIT:
		eGamePhase = GAMEPHASE_RESET;

	case GAMEPHASE_RESET:
		SAFE_DELETE(pScene);
		pScene = new Title(this);
		eGamePhase = GAMEPHASE_TITLE;	// GAMEへDebug
		
	// タイトルシーン
	case GAMEPHASE_TITLE:
		if (pScene != NULL)
			rc = pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(pScene);
		pScene = new Stage(this);
		eGamePhase = GAMEPHASE_GAME;
		
		// ゲームシーン
	case GAMEPHASE_GAME:
		if (pScene != NULL)
			rc = pScene->move();
		else // pScene == NULL
		{
			printf("");		// Debug
		}
		if (rc == GAMESCENE_DEFAULT)
			break;

		eGamePhase = GAMEPHASE_RESET;
	}
	// デバッグ用カウンタ
	count++;
}


/**
* @brief 全体の描画を行う関数
*/
void Selector::doDraw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget) {

	// 1バイトのビット数(2^8)
	TCHAR	str[256];

	//	シーンを描画
	if (pScene != NULL)
		pScene->draw(pRenderTargetView, pRenderTarget);
#ifdef _DEBUG
	//	デバッグ用表示
	D2D1_SIZE_F size;
	//size = pContext->GetSize();

	//_stprintf_s(str, _countof(str), _T("%08d"), count);
	
	//// 左上にタイマー表示
	//D2D1_RECT_F	 rc;	// 描画領域(画面上での位置やサイズ)を指定する変数
	//rc.left = 0;	// 描画領域の左上隅指定
	//rc.top = 0;		//			〃
	//rc.right = size.width;		// 描画領域の右下隅指定
	//rc.bottom = size.height;	//			〃

	////if (WhiteBrush) {
	////	pRenderTarget->DrawText(str, _tcslen(str), TextFormat, &rc, WhiteBrush);
	////}

#endif
}


/**
* @method
* @brief ゲーム画面用のRenderTarget を返す
* @note	このメソッドが返した  は必ずRelease すること
*/
ID3D11RenderTargetView* Selector::GetRenderTarget() {
	RenderTargetView->AddRef();
	return RenderTargetView;
}


/**
* @method
* @brief ゲーム画面用のRenderTarget を返す
* @note	このメソッドが返した  は必ずRelease すること
*/
ID2D1RenderTarget* Selector::GetRenderTarget2D() {	// ここで例外エラー
	RenderTarge->AddRef();
	return RenderTarge;
}


/**
* @method
* @brief	デバッグ用のTextFormat を返す
* @note		このメソッドが返した IDWriteTextFormat は必ずRelease すること
*/
IDWriteTextFormat* Selector::GetTextFormat() {
	TextFormat->AddRef();
	return TextFormat;
}