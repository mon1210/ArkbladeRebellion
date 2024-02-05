/**
* @file		Collision.h
* @brief	クラス Collision の宣言
* @note		プレイヤー・床に対して影響するのでGameで関数使用
*/
#pragma once
#include "DxLib.h"
#include "..\Game\Game.h"
#include "..\GlobalFunctions\GlobalFunctions.h"

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
	* @param[in] push_power　	当たった際の押し戻しの力
	*/
	bool charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR pos2,
		float cap1_height, float cap2_height, float cap1_radius, float cap2_radius,
		float push_power);

	/**
	* @brief  キャラクターが攻撃範囲内にいるか同かを判定するメソッド
	* @note
	* @return true:攻撃範囲の中 / false:攻撃範囲の外
	* @param[in] attack_ch_pos　攻撃しようとしているキャラの座標
	* @param[in] damage_ch_pos　攻撃を受けようとしているキャラの座標
	* @param[in] attack_area　	攻撃範囲
	*/
	bool checkAttackArea(VECTOR attack_ch_pos, VECTOR damage_ch_pos, float attack_area);

	/**
	* @brief  二つのOBBオブジェクトで当たり判定をする
	* @note	  OBB同士の当たり判定をとる
	* @return true:当たっている / false:当たっていない
	* @param[in] obb_01　一つ目のOBB
	* @param[in] obb_02　二つ目のOBB
	*/
	bool checkOBBCol(OBBCollider obb_01, OBBCollider obb_02);
private:
	/**
	* @brief  分離軸候補が、分離軸かどうかを判断
	* @note	  OBBの投影距離と二つの距離比較
	*
	* @return true:分離軸である / false:分離軸ではない
	* @param[in] axis　			分離軸候補
	* @param[in] obb1_vertices　一つ目のOBBの頂点
	* @param[in] obb2_vertices　二つ目のOBBの頂点
	*/
	bool isFindSeparatingAxis(const VECTOR& axis, VECTOR obb1_vertices[8], VECTOR obb2_vertices[8]);

	/**
	* @brief  OBB同士が衝突しているかどうかを判断する
	* @note	  それぞれの辺に対する3方向のベクトル * 2(OBBの数) + 外積分離軸(3 * 3 = 9) = 15で判定
	*		　分離軸判定関数を用いて、全ての軸候補で判断
	*		  「分離軸である」 => 「衝突していない」
	* @return true:衝突している / false:衝突していない
	* @param[in] axis_list　	分離軸の配列[OBBの数]
	* @param[in] vertices_list　OBBの頂点配列[OBBの数][頂点の数]
	*/
	bool checkOBBs(Axis axis_list[2], VECTOR vertices_list[2][8]);
private:
	Game *pGame = nullptr;
	int tileHandle = 0;		// 床モデル保存用

};