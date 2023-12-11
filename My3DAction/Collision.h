/**
* @file		Collider.h
* @brief	クラス Collider の宣言
* @note		プレイヤー・床に対して影響するのでStageで関数使用
*/
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"

// クラスの前方宣言
class Enemy;

class Collision
{
public:
	Collision();
	~Collision();
	virtual void initCollision(int handle);	// 当たり判定を付与する　一度だけStageで呼び出す　今はタイルのみ
	virtual void setTileModel(int model);	// タイルモデルをセットする　Stageで呼び出し

	// 以下3つ未完成
	virtual void chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// キャラ同士の当たり判定
	virtual void clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// プレイヤー移動時のステージとの当たり判定メソッド
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
protected:
	int tileHandle;

};