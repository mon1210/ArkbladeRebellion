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
#include "..\GlobalFunctions\GlobalFunctions.h"

// クラスの前方宣言
class CharaBase;
class Game;

class Player : public CharaBase
{
public:
	Player(Game *Game_);
	~Player() override;
	bool isAlive() override;								// 生き死にを結果として返す　true:生存 / false:死亡
	void draw() override;									// 描画メソッド
	void initialize(int hit_point) override;				// 初期化メソッド
	void update() override;									// 行動管理メソッド
	// 以下取得用定数====================================================================== //
	float	GetHp();										// hitPointを取得して返す
	// 以上取得用定数====================================================================== //
private:
	void initializeStateFunctions() override;				// unordered_map初期化メソッド　各Stateごとの関数登録	
	bool checkMoveKey();									// 移動キーチェック　条件文を簡潔に
	bool checkRollKey();									// 前転キーチェック　条件文を簡潔に
	void manageRollCooldown();								// Rollのクールダウン管理メソッド
	void animateAndMove(ePlayer::AnimationNum num,
		float ROTATE_ANGLE, float move_x, float move_z);	// 移動時の行動管理メソッド
private:
	// 状態ごとのメソッド
	void idle();	// 待機
	void move();	// 移動
	void roll();	// 回転
	void attack();	// 攻撃 => 三段攻撃の予定
	void damage();	// 被ダメージ
	void healing();	// 回復
	void death();	// 死亡
protected:
	Game	*pGame = nullptr;
	int		rollCoolTime = 0;
	float	*withSwordAnimTimes = 0;									// 武器を持ったモデルのアニメーション総再生時間
	bool	isMove = false;												// 移動フラグ
	bool	rollAble = true;											// Roll可能フラグ
	bool	isRoll = false;												// 回転中フラグ
	bool	isDeath = false;											// 死亡フラグ
	bool	isAttackAnim = false;										// 攻撃アニメーションがセットされているかのフラグ

	PlayerState currentState = PlayerState::Idle;						// 状態を表す

	std::unordered_map<PlayerState, StateFunction> stateFunctionMap;	// 関数の入ったunordered_mapを定義
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
#define Key_BackRoll		CheckHitKey(KEY_INPUT_S)
#define Key_Attack			CheckHitKey(KEY_INPUT_V)
#define Key_Healing			CheckHitKey(KEY_INPUT_F)