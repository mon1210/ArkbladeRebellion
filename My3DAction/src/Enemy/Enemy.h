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

// クラスの前方宣言
class CharaBase;
class Game;
class OBBCollider;

class Enemy : public CharaBase
{
public:
	/**
	* @brief Enemyのコンストラクタ
	*/
	Enemy(Game *Game_);

	// デストラクタ
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
	* @param[in] hit_point　キャラのHP　拡張性向上のため
	*/
	void initialize(int hit_point) override;

	/**
	* @brief 行動状態の管理メソッド
	* @note  毎フレームの処理
	*/
	void update() override;

	// 以下取得用定数===================================================================== //
	/**
	* @brief pOBBColを取得して返す
	*/
	OBBCollider *GetOBBCol();
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
	void setStateAndAnim(EnemyState state,eEnemy::AnimationNum anim_num);	// 状態とアニメーションを設定

	/**
	* @brief 座標と当たり判定を設定するメソッド
	* @note  移動時に呼び出し
	*/
	void updateMoveAndCollision() override;

	// 状態ごとのメソッド
	void wait();	// 待機
	void move();	// 移動
	void chase();	// 追跡
	void attack();	// 攻撃
	void damage();	// 被ダメージ
	void death();	// 死亡
private:
	Game		*pGame = nullptr;
	OBBCollider *pOBBCol = nullptr;
	OBBCollider *pOBBColHand = nullptr;
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);						// エネミーからプレイヤーまでの距離
	int		count = 0;												// フレーム計測用　行動遷移, で使用 
	float   vecLength = 0.f;										// ベクトルの長さ保存用
	float	animTime = 0.f;											// アニメーション時間保存用変数　Enemyは毎フレーム状態変数を通らないので必要
	bool	isColHit = false;										// 当たり判定が接触したかどうか
	bool	isAttack = false;										// 攻撃状態かどうか

	EnemyState currentState = EnemyState::Wait;						// 状態を表す

	std::unordered_map<EnemyState, StateFunction> stateFunctionMap;	// 関数の入ったunordered_mapを定義
};