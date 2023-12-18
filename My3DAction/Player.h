/*
* @file		Player.h
* @brief	クラス Player の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "CharaBase.h"

#include "Animation.h"
#include "Constants.h"
#include "Enums.h"
#include "Game.h"

// クラスの前方宣言
class CharaBase;
class Game;

class Player : public CharaBase
{
public:
	Player(Game *Game_);
	~Player();
	bool move() override;									// アニメーションメソッド
	void draw() override;									// 描画メソッド
	void update() override;									// 行動管理メソッド
	void moveHandle(ePlayer::AnimationNum num, 
		float ROTATE_ANGLE, float move_x, float move_z);	// 移動時の行動管理メソッド
	// 以下取得用定数====================================================================== //
	VECTOR  GetPos() override;								// 座標を取得して返すメソッド
	// 以上取得用定数====================================================================== //
protected:
	Game	*pGame = NULL;
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);	// 移動の向きベクトル
	bool	isMove = false;				// 移動フラグ
	bool	rollAble = true;				// Roll可能フラグ
};


// マクロ定義
#define VECTOR_SCALING	0.70710678118f	// 斜め入力用の各軸の倍率( sin( 45°) )
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_Roll			CheckHitKey(KEY_INPUT_SPACE)