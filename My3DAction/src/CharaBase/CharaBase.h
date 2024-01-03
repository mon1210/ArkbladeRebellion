/**
* @file		CharaBase.h
* @brief	クラスCharaBaseの宣言ファイル
* @note		Characterの基底クラスで、PlayerとEnemyが継承している
*			基底クラスでは、共通する関数と変数をまとめて宣言
*/
#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <functional>

// 基底クラス
class CharaBase 
{
public:
	virtual ~CharaBase();
	virtual bool isAlive() = 0;						// 生き死にを結果として返す　true:生存 / false:死亡
	virtual void draw() = 0;						// 描画メソッド
	virtual void update() = 0;						// 更新メソッド
	virtual void initializeStateFunctions() = 0;	// unordered_map初期化メソッド　各Stateごとの関数登録
	virtual void initializeAnimationList() = 0;		// animationList初期化メソッド
	// 以下取得用定数===================================================================== //
	VECTOR GetPos() { return position; };			// 座標を取得して返す
	// 以上取得用定数===================================================================== //
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);			// 座標
	int		animHandle = 0;							// モデルハンドル
	int		animNum = 0;							// アニメーション番号
	float   *animTimes = 0;							// アニメーションの総再生時間
	float	animTimer = 0.f;						// アニメーションの現在の再生時間
	float	angle = 0.f;							// 向き		アタッチ時にradに変換
	float	hitPoint = 100.f;						// HP
	//float damage
	typedef std::function<void()> StateFunction;	// 関数ポインタの型を定義
};