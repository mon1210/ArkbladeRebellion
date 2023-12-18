/**
* @file		SceneManager.h
* @brief	クラスSceneManagerの宣言ファイル
*/
#pragma once
#include "IGameScene.h"
#include "Enums.h"

class IGameScene;	// シーン管理クラス

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager(void);
	void doAnim();							// ゲーム全体のアニメート
	void doDraw();							// ゲーム全体の描画
	void fadeOut();							// シーン遷移時のフェードアウト処理　Todo 未完成
	int clamp(int value, int min, int max)	// 値を指定された範囲内に収めるメソッド
	{
		if (value < min)return min; 
		else if (value > max)return max;
		else return value;
	}
protected:
	IGameScene *pScene = NULL;				//	シーン
	GamePhase GamePhase = GAMEPHASE_INIT;	//	状態変数
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

