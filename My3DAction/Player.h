/*
* @file		Player.h
* @brief	クラス Player の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "IGameObject.h"

class Stage;
class Camera;
class Collider;
class Model;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	virtual bool move() override;	// アニメーションメソッド
	virtual void draw() override;	// 描画メソッド
	virtual void SetMove();			// 行動管理関数
	virtual void SetAnim(ePlayer::AnimationNum num);	// アニメーションセット関数
	virtual void RollAnim();		// Rollのアニメーションメソッド
	VECTOR*	GetPlayerPos();			// 座標取得関数
protected:
	Camera*		pCamera;
	Collider*	pCollider;
	Model*		pModel;
	VECTOR	position;	// 座標
	VECTOR* pPlayerPos;	// 
	VECTOR	moveVec;	// 移動の向きベクトル
	int		animHandle;	// モデルハンドル
	int		animNo;		// アニメーション番号
	float	animTime;	// アニメーションの総再生時間
	float	animTimer;	// アニメーションの現在の再生時間
	float	angle;		// プレイヤーの向き
	float	hitPoint;	// HP
	bool	moveFlag;	// 移動フラグ
	bool	rollAble;	// Roll可能フラグ
private:

};
