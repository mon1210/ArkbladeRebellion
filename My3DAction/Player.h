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
class Collider;

class Player : public IGameObject
{
public:
	Player(Stage *parent);
	~Player();
	virtual bool move() override;	// アニメーションメソッド
	virtual void draw() override;	// 描画メソッド
	virtual void SetMove();			// 行動管理関数
	virtual void SetAnim(ePlayer::AnimationNum num);	// アニメーションセット関数
	virtual void RollAnim();		// Rollのアニメーションメソッド
	VECTOR  GetPlayerPos();			// 座標取得関数
	VECTOR  GetPlayerMoveVec();		// 
	virtual void setPlayerModel(int model);
	virtual void setCameraHAngle(float camera_H_A);
	virtual void setPlayerNewPos(VECTOR new_pos);
protected:
	Collider	*pCollider;
	VECTOR	position;	// 座標
	VECTOR  newPos;		// 
	VECTOR	moveVec;	// 移動の向きベクトル
	int		animHandle;	// モデルハンドル
	int		animNo;		// アニメーション番号
	float	animTime;	// アニメーションの総再生時間
	float	animTimer;	// アニメーションの現在の再生時間
	float	angle;		// プレイヤーの向き
	float	hitPoint;	// HP
	float   cameraHA;	// カメラの水平角度  CameraHorizontalAngle
	bool	moveFlag;	// 移動フラグ
	bool	rollAble;	// Roll可能フラグ
private:

};
