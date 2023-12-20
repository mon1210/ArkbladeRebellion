/*
* @file		Player.h
* @brief	クラス Player の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "..\CharaBase\CharaBase.h"

#include "..\Animation\Animation.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\Game\Game.h"

// クラスの前方宣言
class CharaBase;
class Game;

class Player : public CharaBase
{
public:
	Player(Game *Game_);
	~Player();
	bool isAlive() override;								// 生き死にを結果として返す　true:生存 / false:死亡
	void draw() override;									// 描画メソッド
	void update() override;									// 行動管理メソッド
	bool checkMoveKey();									// 移動キーチェック　条件文を簡潔に
	bool checkRollKey();									// 前転キーチェック　条件文を簡潔に
	void animateAndMove(ePlayer::AnimationNum num,
		float ROTATE_ANGLE, float move_x, float move_z);	// 移動時の行動管理メソッド
	// 以下取得用定数====================================================================== //
	VECTOR  GetPos() override;								// 座標を取得して返すメソッド
	float	GetHp();										// hitPointを取得して返す
	// 以上取得用定数====================================================================== //
private:
	// 状態ごとのメソッド
	void Idle();	// 待機
	void Move();	// 移動
	void Roll();	// 前転
	void Attack();	// 攻撃 => 三段攻撃の予定
	void Damage();	// 被ダメージ
	void Healing();	// 回復
	void Death();	// 死亡
protected:
	Game	*pGame = NULL;
	VECTOR	moveVec = VGet(0.f, 0.f, 0.f);			// 移動の向きベクトル
	bool	isMove = false;							// 移動フラグ
	bool	rollAble = true;						// Roll可能フラグ

	PlayerState currentState = PlayerState::Idle;	// 状態を表す
};


// マクロ定義
#define VECTOR_SCALING	0.70710678118f	// 斜め入力用の各軸の倍率( sin( 45°) )
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_UP)
#define Key_BackMove		CheckHitKey(KEY_INPUT_DOWN)
#define Key_RightMove		CheckHitKey(KEY_INPUT_RIGHT)
#define Key_Left_Move		CheckHitKey(KEY_INPUT_LEFT)
#define Key_ForwardRoll		CheckHitKey(KEY_INPUT_W)
#define Key_RightRoll		CheckHitKey(KEY_INPUT_D)
#define Key_LeftRoll		CheckHitKey(KEY_INPUT_A)