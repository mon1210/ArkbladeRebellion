/**
* @file		Enemy.h
* @brief	クラス Enemy の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "BG.h"
#include "Player.h"
#include "Constants.h"
#include "IGameObject.h"


class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	virtual void InitAnimation();	// アニメーション状態初期化関数 Stageで初期化時一度だけ呼び出す
	virtual void Update();			// 状態管理とdraw呼び出し　毎フレーム呼び出される
	virtual bool IsTargetVisible();	// エネミーの視野　true : 視野内にプレイヤーがいる / false : 視野外にプレイヤーがいる 
	virtual bool move() override;	// エネミーのアニメーションメソッド　true:生存 / false:死亡
	virtual void draw() override;	// 描画メソッド
	virtual void SetMove();			// 行動管理メソッド　デバッグ用　削除予定 Todo
	virtual void SetAnim(eEnemy::AnimationNum num);	// アニメーションセットメソッド
	virtual VECTOR GetEnemyPos();	// 座標取得メソッド
	virtual void setEnemyModel(int model);			// エネミーのモデルをセットする
	virtual void setTileModel(int model);			// タイルのモデルをセットする　 タイル => 当たり判定で使用
	virtual void setPlayerPos(VECTOR player_pos);	// プレイヤーの座標をセットする
private:
	// 状態ごとのメソッド
	virtual void Wait();
	virtual void Move();
	virtual void Chase();
protected:
	VECTOR	position;
	VECTOR  playerPos;		// enemyToPlayerを求めるのに使用
	VECTOR  enemyToPlayer;	// エネミーからプレイヤーまでの距離
	int		animHandle;
	int		tileHandle;
	int		animNo;
	int		count;			// フレーム計測用　行動遷移, で使用 
	float	animTime;
	float	animTimer;
	float	angle;
	float	hitPoint;
	float   vecLength;		// ベクトルの長さ保存用

	EnemyState currentState;
private:


};