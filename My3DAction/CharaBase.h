/**
* @file		CharaBase.h
* @brief	クラスCharaBaseの宣言ファイル
* @note		Characterの基底クラスで、PlayerとEnemyが継承している
*			基底クラスでは、共通する関数と変数をまとめて宣言
*/
#pragma once
#include "DxLib.h"

// 基底クラス
class CharaBase 
{
public:
	virtual ~CharaBase();
	virtual bool move() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual VECTOR getPos() = 0;
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);	// 座標
	int		animHandle = 0;					// モデルハンドル
	int		animNo = 0;						// アニメーション番号
	float	animTime = 0.f;					// アニメーションの総再生時間
	float	animTimer = 0.f;				// アニメーションの現在の再生時間
	float	angle = 0.f;					// 向き		アタッチ時にradに変換
	float	hitPoint = 100.f;				// HP
	//float damage
};