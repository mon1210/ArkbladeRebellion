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
	~Enemy();
	void initAnimation();								// アニメーション状態初期化関数 Stageで初期化時一度だけ呼び出す
	bool isAlive() override;							// 生き死にを結果として返す　true:生存 / false:死亡
	void draw() override;								// 描画メソッド
	void update() override;								// 状態管理とdraw呼び出し　毎フレーム呼び出される
	void initializeStateFunctions() override;			// unordered_map初期化メソッド　各Stateごとの関数登録	
	bool isTargetVisible();								// エネミーの視野　true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる 
	void setAnimationHandle(eEnemy::AnimationNum num);	// アニメーションを設定する
	void updateToPlayerVec();							// enemyToPlayerの更新・長さを算出　毎フレーム呼び出す
	// 以下取得用定数===================================================================== //
	VECTOR GetPos() override;							// 座標取得メソッド
	// 以上取得用定数===================================================================== //
private:
	// 状態ごとのメソッド
	virtual void Wait();	// 待機
	virtual void Move();	// 移動
	virtual void Chase();	// 追跡
protected:
	Game	*pGame = nullptr;
	VECTOR  toPlayerVec = VGet(0.f, 0.f, 0.f);						// エネミーからプレイヤーまでの距離
	int		tileHandle = 0;											// 床モデルハンドル
	int		count = 0;												// フレーム計測用　行動遷移, で使用 
	float   vecLength = 0.f;										// ベクトルの長さ保存用

	EnemyState currentState = EnemyState::Wait;						// 状態を表す

	std::unordered_map<EnemyState, StateFunction> stateFunctionMap;	// 関数の入ったunordered_mapを定義
};