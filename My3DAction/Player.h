/*
* @file		Player.h
* @brief	クラス Player の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"
#include "Constants.h"
#include "Collision.h"
#include "Stage.h"
#include "Radar.h"
#include "IGameObject.h"

// クラスの前方宣言
class Stage;
class Collider;
class Radar;

class Player : public IGameObject
{
public:
	Player(Stage *parent);
	~Player();
	bool move() override;	// アニメーションメソッド
	void draw() override;	// 描画メソッド
	void setMove();			// 行動管理メソッド
	void setAnim(ePlayer::AnimationNum num);  // アニメーションセットメソッド
	void rollAnim();		// Rollのアニメーションメソッド
	VECTOR  getPlayerPos();			// 座標を取得して返すメソッド
	VECTOR  getPlayerMoveVec();		// Playerの移動方向を取得して返すメソッド
	void setPlayerModel(int model);				// プレイヤーのモデルをセットするメソッド
	void setCameraHAngle(float camera_H_A);		// カメラの水平方向の角度をセットするメソッド
	void setPlayerNewPos(VECTOR new_pos);		// プレイヤーの移動後の新しい座標をセットするメソッド
protected:
	Collision *pCollision;
	Radar	  *pRadar;
	VECTOR	position;	// 座標
	VECTOR  newPos;		// 移動後の座標保存用
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
};


// マクロ定義
#define VECTOR_SCALING	0.70710678118f	// 斜め入力用の各軸の倍率( sin( 45°) )
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_Roll			CheckHitKey(KEY_INPUT_SPACE)