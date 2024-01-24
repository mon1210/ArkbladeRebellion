/**
* @file		Collision.h
* @brief	クラス Collision の宣言
* @note		プレイヤー・床に対して影響するのでGameで関数使用
*/
#pragma once
#include "DxLib.h"
#include "..\Game\Game.h"

// クラスの前方宣言
class Game;

class Collision
{
public:
	/**
	* @brief Collisionのコンストラクタ
	*/
	Collision(Game *Game_);

	// デストラクタ
	~Collision();

	/**
	* @brief 当たり判定初期化
	* @note  床に当たり判定付与
	*/
	void initialize(int handle);

	/**
	* @brief  移動時のステージとの当たり判定メソッド
	* @note   移動範囲を制限している
	* @return true:判定あり、移動可 / false:判定なし、移動不可
	*/
	bool clampToStageBounds(VECTOR& new_pos, VECTOR& pos);

	/**
	* @brief  キャラ同士のカプセル当たり判定メソッド
	* @note   キャラの移動時に呼び出している
	* @return true:当たっている / false:当たっていない
	* @param[in] pos1　			移動しているキャラの座標
	* @param[in] pos1_move_vec　移動しているキャラの移動ベクトル
	* @param[in] pos2　			当たられる側の座標
	* @param[in] cap1_height　	pos1のカプセルの高さ
	* @param[in] cap2_height　	pos2のカプセルの高さ
	* @param[in] cap1_radius　	pos1のカプセルの半径
	* @param[in] cap2_radius　	pos2のカプセルの半径
	*/
	bool charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR pos2,
		float cap1_height, float cap2_height, float cap1_radius, float cap2_radius);

	/**
	* @brief  キャラクターが攻撃範囲内にいるか同かを判定するメソッド
	* @note
	* @return true:攻撃範囲の中 / false:攻撃範囲の外
	* @param[in] attack_ch_pos　攻撃しようとしているキャラの座標
	* @param[in] damage_ch_pos　攻撃を受けようとしているキャラの座標
	* @param[in] attack_area　	攻撃範囲
	*/
	bool checkAttackArea(VECTOR attack_ch_pos, VECTOR damage_ch_pos, float attack_area);
private:
	Game *pGame = nullptr;
	int tileHandle = 0;		// 床モデル保存用

};