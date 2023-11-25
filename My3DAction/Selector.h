/**
* @file		Selector.h
* @brief	クラスSelectorの宣言ファイル
*/
#pragma once
// 定数値を定めたヘッダファイル
#include "Constants.h"
// 
#include "Player.h"
// 
#include "Model.h"

//--- ヘッダガードで、同じヘッダファイルが複数回インクルードされることによる問題を防いでいる
#ifndef __IGAMESCENE_H__
#include "IGameScene.h"
#endif

enum eGamePhase {
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200
};

enum GameSceneResultCode {
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

class IGameScene;	// シーン管理クラス
class Player;
class Model;

class Selector
{
public:
	Selector();
	virtual ~Selector(void);
	void doAnim();		//	ゲーム全体のアニメート
	void doDraw();	//	ゲーム全体の描画
protected:

	Player* pPlayer;
	IGameScene* pScene;		//	シーン
	eGamePhase eGamePhase;	//	状態変数
	//INT m_iWait;
	INT		count;	//	カウンター(デバッグ用)
};

//	マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

