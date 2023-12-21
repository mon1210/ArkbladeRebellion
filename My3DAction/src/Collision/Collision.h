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
	Collision(Game *Game_);
	~Collision();
	void initCollision(int handle);														// 当たり判定を付与する　一度だけStageで呼び出す　今はタイルのみ
	void clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);		// プレイヤー移動時のステージとの当たり判定メソッド
	void charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR& pos2, 
		float CAP1_HEIGHT, float CAP2_HEIGHT, float CAP1_RADIUS, float CAP2_RADIUS);	// キャラ同士のカプセル当たり判定メソッド
protected:
	Game *pGame = nullptr;
	int tileHandle = 0;		// 床モデル保存用

};