/**
* @file		CharaBase.h
* @brief	クラス CharaBase の宣言
* @note		Characterの基底クラスで、PlayerとEnemyが継承している
*			基底クラスでは、共通する関数と変数をまとめて宣言
*/
#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <functional>

//! 基底クラス
class CharaBase 
{
public:
	/**
	* @brief 純粋仮想デストラクタの実体
	* @note  デストラクタだけは用意しなければ、サブクラスがデストラクタを呼べない
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
	* @note  拡張性を考慮し引数にHPを指定
	* @param[in] hit_point  キャラのHP
	*/
	virtual void initialize(float hit_point) = 0;

	/**
	* @brief 行動状態の管理メソッド
	* @note  毎フレームの処理
	*/
	virtual void update() = 0;

	// 以下取得用定数===================================================================== //
	/**
	* @brief 座標を取得して返す
	*/
	VECTOR GetPos() { return position; }

	/**
	* @brief Hpを取得して返す
	*/
	int	GetHp() { return hitPoint; }

	/**
	* @brief 攻撃ヒット判定フラグを取得して返す
	*/
	bool GetIsHitFlag() { return isAttackHit; }

	/**
	* @brief 一度の攻撃で二段攻撃にならないようにするフラグを取得して返す
	*/
	bool GetDamegeFlag() { return isDamageCooldown; }
	// 以上取得用定数===================================================================== //

	/**
	* @brief 一度の攻撃で二段攻撃にならないようにするフラグをセットする
	* @param[in] is_damage_flag 一度の攻撃で二段攻撃にならないようにするフラグ
	*/
	void SetDamegeFlag(bool is_damage_flag) { isDamageCooldown = is_damage_flag; }
protected:
	/**
	* @brief unordered_map初期化メソッド
	* @note  各Stateごとのメソッドを登録
	*/
	virtual void initializeStateFunctions() = 0;

	/**
	* @brief 移動後の座標を設定する
	* @note  移動時に呼び出し
	*/
	virtual void moveHandle() = 0;
protected:
	//! 座標
	VECTOR	position = VGet(0.f, 0.f, 0.f);
	//! 移動の向きベクトル
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);
	//! モデルハンドル
	int		animHandle = 0;
	//! アニメーション番号
	int		animNum = 0;
	//! HP
	int		hitPoint = 100;
	//! アニメーションの総再生時間
	float  *animTimes = 0;
	//! アニメーションの現在の再生時間
	float	animTimer = 0.f;
	//! 向き		アタッチ時にradに変換
	float	angle = 0.f;
	//! HPが変化したかを判断する用の変数
	float	currentHP = 0.f;
	//! 死亡フラグ
	bool	isDeath = false;
	//! 自身の攻撃が当たったかのフラグ
	bool	isAttackHit = false;
	//! 一度の攻撃で二段攻撃にならないようにするフラグ
	bool	isDamageCooldown = false;

	//!  関数ポインタの型を定義
	typedef std::function<void()> stateFunction;
};