/**
* @file		Player.h
* @brief	クラス Player の宣言
*/
#pragma once
#include "..\CharaBase\CharaBase.h"

#include "..\Animation\Animation.h"
#include "..\Constants.h"
#include "..\Enums.h"
#include "..\Game\Game.h"
#include "..\GlobalFunctions\GlobalFunctions.h"
#include "..\OBBCollider\OBBCollider.h"

//! クラスの前方宣言
class CharaBase;
class Game;
class OBBCollider;

class Player : public CharaBase
{
public:
	/**
	* @brief Playerのコンストラクタ
	*/
	Player(Game *Game);

	/**
	* @brief Playerのデストラクタ
	*/
	~Player() override;

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
	* @note  拡張性を考慮し引数にHPを指定
	* @param[in] hit_point  キャラのHP
	*/
	void initialize(int hit_point) override;

	/**
	* @brief 行動状態の管理メソッド
	* @note  毎フレームの処理
	*/
	void update() override;

	// 以下取得用定数====================================================================== //
	/**
	* @brief healCountを取得して返す
	*/
	int		GetHealCount();

	/**
	* @brief mOBBColを取得して返す
	*/
	OBBCollider GetOBBCol();
	// 以上取得用定数====================================================================== //
private:
	/**
	* @brief unordered_map初期化メソッド
	* @note  各Stateごとのメソッドを登録
	*/
	void initializeStateFunctions() override;

	/**
	* @brief 　移動キーチェック
	* @details 条件文を簡潔に
	*/
	bool checkMoveKey();

	/**
	* @brief 　回転キーチェック
	* @details 条件文を簡潔に
	*/
	bool checkRollKey();

	/**
	* @brief Rollのクールダウン管理メソッド
	* @note  クールタイムを減らし、0になるとRollをできるように
	*/
	void manageRollCooldown();

	/**
	* @brief AttackからIdleに戻る際の処理メソッド
	*/
	void changeAttackToIdle();

	/**
	* @brief 移動後の座標を設定する
	* @note  移動時に呼び出し
	*/
	void moveHandle() override;

	/**
	* @brief 移動時の行動管理
	* @note  アニメーションと向きの設定をする
	*        moveFlagはここでtrueに
	* @param[in] num　	        アニメーション番号
	* @param[in] rotate_angle　	回転角度
	* @param[in] move_x　	    x軸方向の移動スピード
	* @param[in] move_z　	    z軸方向の移動スピード
	*/
	void animateAndMove(ePlayer::AnimationNum num, float rotate_angle, float move_x, float move_z);
private:
	// 以下 状態ごとのメソッド ---------------------
	/**
	* @brief 待機状態の管理メソッド
	*/
	void idle();

	/**
	* @brief 移動状態の管理メソッド
	*/
	void move();

	/**
	* @brief 回転状態の管理メソッド
	*/
	void roll();

	/**
	* @brief 攻撃状態の管理メソッド
	*/
	void attack();

	/**
	* @brief 被ダメージ状態の管理メソッド
	*/
	void damage();

	/**
	* @brief 回復状態の管理メソッド
	*/
	void healing();

	/**
	* @brief 死亡状態の管理メソッド
	*/
	void death();
	// 以上 状態ごとのメソッド ---------------------
private:
	//! 体用 OBBColliderインスタンス化   被ダメージ時使用
	OBBCollider mOBBCol = OBBCollider(PLAYER_OBB_SCALE, PLAYER_OBB_ANGLE, PLAYER_OBB_TRANS);

	//! 剣用 OBBColliderインスタンス化   攻撃時使用
	OBBCollider mOBBColSword = OBBCollider(SWORD_OBB_SCALE, SWORD_OBB_ANGLE, SWORD_OBB_TRANS);
private:
	Game	*pGame = nullptr;
	//! 回復可能回数
	int		healCount = 0;
	//! 回転のクールタイム管理変数
	float	rollCoolTime = 0.f;
	//! 武器を持ったモデルのアニメーション総再生時間
	float	*withSwordAnimTimes = 0;
	//! Roll可能フラグ
	bool	rollAble = true;
	//! 回転中フラグ
	bool	isRoll = false;
	//! 攻撃アニメーションがセットされているかのフラグ
	bool	isAttackAnim = false;
	//! 一段目の攻撃かどうかのフラグ
	bool	isFirst = false;
	//! 二段目の攻撃かどうかのフラグ
	bool	isSecond = false;
	//! 三段目の攻撃かどうかのフラグ
	bool	isThird = false;
	
	//! 状態を表す
	PlayerState currentState = PlayerState::Idle;

	//! 関数の入ったunordered_mapを定義
	std::unordered_map<PlayerState, stateFunction> stateFunctionMap;
};


//	以下 マクロ定義
/**
* @def Key_ForwardMove
* @brief 前進キーの入力を判定
*/
#define Key_ForwardMove		CheckHitKey(KEY_INPUT_W)
/**
* @def Key_BackMove
* @brief 後退キーの入力を判定
*/
#define Key_BackMove		CheckHitKey(KEY_INPUT_S)
/**
* @def Key_RightMove
* @brief 右移動キーの入力を判定
*/
#define Key_RightMove		CheckHitKey(KEY_INPUT_D)
/**
* @def Key_Left_Move
* @brief 左移動キーの入力を判定
*/
#define Key_Left_Move		CheckHitKey(KEY_INPUT_A)

/**
* @def Key_ForwardRoll
* @brief 前転キーの入力を判定
*/
#define Key_ForwardRoll		CheckHitKey(KEY_INPUT_UP)
/**
* @def Key_RightRoll
* @brief 右回転キーの入力を判定
*/
#define Key_RightRoll		CheckHitKey(KEY_INPUT_RIGHT)
/**
* @def Key_LeftRoll
* @brief 左回転キーの入力を判定
*/
#define Key_LeftRoll		CheckHitKey(KEY_INPUT_LEFT)
/**
* @def Key_BackRoll
* @brief 後ろ回転キーの入力を判定
*/
#define Key_BackRoll		CheckHitKey(KEY_INPUT_DOWN)

/**
* @def Key_Attack
* @brief 攻撃キーの入力を判定
*/
#define Key_Attack			CheckHitKey(KEY_INPUT_V)
/**
* @def Key_Healing
* @brief 回復キーの入力を判定
*/
#define Key_Healing			CheckHitKey(KEY_INPUT_C)