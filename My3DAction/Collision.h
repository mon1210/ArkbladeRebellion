/**
* @file		Collision.h
* @brief	クラス Collision の宣言
* @note		プレイヤー・床に対して影響するのでGameで関数使用
*/
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"

// クラスの前方宣言
class Enemy;
class Game;

class Collision
{
public:
	Collision(Game *Game_);
	~Collision();
	virtual void initCollision(int handle);	// 当たり判定を付与する　一度だけStageで呼び出す　今はタイルのみ

	// 以下3つ未完成
	virtual void chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// キャラ同士の当たり判定
	virtual void clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// プレイヤー移動時のステージとの当たり判定メソッド
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
protected:
	int tileHandle;

};