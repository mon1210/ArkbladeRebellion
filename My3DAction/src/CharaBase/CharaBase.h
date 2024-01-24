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
	/**
	* @brief   純粋仮想デストラクタの実体
	* @details デストラクタだけは用意しなければ、サブクラスがデストラクタを呼べない
	*/
	virtual ~CharaBase();

	/**
	* @brief  生き死にを結果として返す
	* @return true:生存 / false:死亡
	*/
	virtual bool isAlive() = 0;

	/**
	* @brief 描画メソッド
	*/
	virtual void draw() = 0;

	/**
	* @brief 初期化メソッド
	* @param[in] hit_point　キャラのHP　拡張性向上のため
	*/
	virtual void initialize(int hit_point) = 0;

	/**
	* @brief 行動状態の管理メソッド
	* @note  毎フレームの処理
	*/
	virtual void update() = 0;

	// 以下取得用定数===================================================================== //
	/**
	* @brief 座標を取得して返す
	*/
	VECTOR GetPos() { return position; };
	// 以上取得用定数===================================================================== //
protected:
	/**
	* @brief unordered_map初期化メソッド
	* @note  各Stateごとのメソッドを登録
	*/
	virtual void initializeStateFunctions() = 0;

	/**
	* @brief 座標と当たり判定を設定するメソッド
	* @note  移動時に呼び出し
	*/
	virtual void updateMoveAndCollision() = 0;
protected:
	VECTOR	position = VGet(0.f, 0.f, 0.f);			// 座標
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);			// 移動の向きベクトル
	VECTOR	obbTrans = VGet(0.f, 0.f, 0.f);			// 当たり判定OBBの移動値
	VECTOR	obbAngle = VGet(0.f, 0.f, 0.f);			// 当たり判定OBBの回転値
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