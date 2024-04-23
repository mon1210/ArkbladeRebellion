/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
*/
#pragma once
#include "..\CharaBase\CharaBase.h"

#include <math.h>
#include "..\BG\BG.h"
#include "..\Player\Player.h"
#include "..\Animation\Animation.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\Game\Game.h"
#include "..\OBBCollider\OBBCollider.h"

//! クラスの前方宣言
class CharaBase;
class Game;
class OBBCollider;

class Enemy : public CharaBase
{
public:
	/**
	* @brief Enemyのコンストラクタ
	*/
	Enemy(Game *Game);

	/**
	* @brief Enemyのデストラクタ
	*/
	~Enemy() override;

	/**
	* @brief  生き死にを結果として返す
	* @return true:生存 / false:死亡
	*/
	bool isAlive() override;

	/**
	* @brief 描画メソッド
	*/
	void draw() override;

	/**
	* @brief 初期化メソッド
	* @note  拡張性を考慮し引数にHPを指定
	* @param[in] hit_point  キャラのHP
	*/
	void initialize(int hit_point) override;

	/**
	* @brief 行動状態の管理メソッド
	* @note  毎フレームの処理
	*/
	void update() override;

	// 以下取得用定数===================================================================== //
	/**
	* @brief mOBBColを取得して返す
	*/
	OBBCollider GetOBBCol();
	// 以上取得用定数===================================================================== //
private:
	/**
	* @brief unordered_map初期化メソッド
	* @note  各Stateごとのメソッドを登録
	*/
	void initializeStateFunctions() override;

	/**
	* @brief   エネミーの視野メソッド
	* @return  true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる
	*/
	bool isTargetVisible();

	/**
	* @brief enemyToPlayerの更新・長さを算出　毎フレーム呼び出す
	* @note  毎フレームの処理
	*/
	void updateToPlayerVec();

	/**
	* @brief 状態とアニメーションを設定
	* @note  状態変更時に使用
	* @param[in] state  変更先の状態
	* @param[in] num    変更先のアニメーション
	*/
	void setStateAndAnim(EnemyState state, eEnemy::AnimationNum anim_num);

	/**
	* @brief 移動後の座標を設定する
	* @note  移動時に呼び出し
	*/
	void moveHandle() override;

	// 以下 状態ごとのメソッド ---------------------
	/**
	* @brief 待機状態の管理メソッド
	*/
	void wait();

	/**
	* @brief 移動状態の管理メソッド
	*/
	void move();

	/**
	* @brief 追跡状態の管理メソッド
	*/
	void chase();

	/**
	* @brief 攻撃状態の管理メソッド
	*/
	void attack();

	/**
	* @brief 被ダメージ状態の管理メソッド
	*/
	void damage();

	/**
	* @brief 死亡状態の管理メソッド
	*/
	void death();
	// 以上 状態ごとのメソッド ---------------------
private:
	//! OBBColliderインスタンス化   被ダメージ時使用　体
	OBBCollider mOBBCol = OBBCollider(ENEMY_OBB_SCALE, ENEMY_OBB_ANGLE, ENEMY_OBB_TRANS);

	//! OBBColliderインスタンス化   攻撃時使用　手
	OBBCollider mOBBColHand = OBBCollider(HAND_OBB_SCALE, HAND_OBB_ANGLE, HAND_OBB_TRANS);
private:
	Game	*pGame = nullptr;
	//! エネミーからプレイヤーまでの距離
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);
	//! フレーム計測用　行動遷移, で使用 
	int		count = 0;
	//! ベクトルの長さ保存用
	float   vecLength = 0.f;
	//! アニメーション時間保存用変数　Enemyは毎フレーム状態変数を通らないので必要
	float	animTime = 0.f;
	//! 当たり判定が接触したかどうか
	bool	isColHit = false;
	//! 攻撃状態かどうか
	bool	isAttack = false;

	//! 状態を表す
	EnemyState currentState = EnemyState::Wait;

	//! 関数の入ったunordered_mapを定義
	std::unordered_map<EnemyState, stateFunction> stateFunctionMap;
};