/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
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

// クラスの前方宣言
class CharaBase;
class Game;

class Enemy : public CharaBase
{
public:
	Enemy(Game *Game_);
	~Enemy() override;
	bool isAlive() override;							// 生き死にを結果として返す　true:生存 / false:死亡
	void draw() override;								// 描画メソッド
	void initialize(int hit_point) override;			// 初期化メソッド
	void update() override;								// 状態管理とdraw呼び出し　毎フレーム呼び出される
private:
	void initializeStateFunctions() override;			// unordered_map初期化メソッド　各Stateごとの関数登録
	bool isTargetVisible();								// エネミーの視野　true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる
	void updateToPlayerVec();							// enemyToPlayerの更新・長さを算出　毎フレーム呼び出す
	void setStateAndAnim(EnemyState state,
					 eEnemy::AnimationNum anim_num);	// 状態とアニメーションを設定
	// 状態ごとのメソッド
	void wait();	// 待機
	void move();	// 移動
	void chase();	// 追跡
	void attack();	// 
protected:
	Game	*pGame = nullptr;
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);						// エネミーからプレイヤーまでの距離
	int		count = 0;												// フレーム計測用　行動遷移, で使用 
	float   vecLength = 0.f;										// ベクトルの長さ保存用
	float	animTime = 0.f;											// アニメーション時間保存用変数　Enemyは毎フレーム状態変数を通らないので必要
	bool	isColHit = false;										// 当たり判定が接触したかどうか
	bool	isAttack = false;										// 攻撃状態かどうか

	EnemyState currentState = EnemyState::Wait;						// 状態を表す

	std::unordered_map<EnemyState, StateFunction> stateFunctionMap;	// 関数の入ったunordered_mapを定義
};