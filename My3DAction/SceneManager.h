/**
* @file		SceneManager.h
* @brief	クラスSceneManagerの宣言ファイル
*/
#pragma once
#include "IGameScene.h"

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

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager(void);
	void doAnim();							// ゲーム全体のアニメート
	void doDraw();							// ゲーム全体の描画
	void FadeOut();							// シーン遷移時のフェードアウト処理　Todo 未完成
	int Clamp(int value, int min, int max)	// 値を指定された範囲内に収めるメソッド
	{
		if (value < min)return min; 
		else if (value > max)return max;
		else return value;
	}
protected:
	IGameScene *pScene = NULL;				//	シーン
	eGamePhase eGamePhase = GAMEPHASE_INIT;	//	状態変数
	int fadeTimer = 0;						// フェードタイマー
	int fadeTime = 0;						// フェード時間（フレーム）
	int startTime = 0;						// 開始時間
};

//	マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

