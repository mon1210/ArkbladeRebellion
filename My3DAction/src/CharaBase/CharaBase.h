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
	virtual void initialize(int hit_point) = 0;		// 初期化メソッド
	virtual void update() = 0;						// 更新メソッド
	virtual void initializeStateFunctions() = 0;	// unordered_map初期化メソッド　各Stateごとの関数登録
	// 以下取得用定数===================================================================== //
	VECTOR GetPos() { return position; };			// 座標を取得して返す
	// 以上取得用定数===================================================================== //
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);			// 座標
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);			// 移動の向きベクトル
	int		animHandle = 0;							// モデルハンドル
	int		animNum = 0;							// アニメーション番号
	float   *animTimes = 0;							// アニメーションの総再生時間
	float	animTimer = 0.f;						// アニメーションの現在の再生時間
	float	angle = 0.f;							// 向き		アタッチ時にradに変換
	float	hitPoint = 100.f;						// HP
	float	currentHP = 0.f;						// HPが変化したかを判断する用の変数
	//float damage
	bool	isDeath = false;						// 死亡フラグ

	typedef std::function<void()> StateFunction;	// 関数ポインタの型を定義
};