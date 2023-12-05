/**
* @file		Collider.h
* @brief	当たり判定に関することを定めたヘッダファイル
* @note		
*/
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"

// クラスの前方宣言
class Enemy;

class Collider
{
public:
	Collider();
	~Collider();
	virtual void InitCollision(int handle);	// 当たり判定を付与する　一度だけStageで呼び出す　今はタイルのみ
	virtual void setTileModel(int model);	// タイルモデルをセットする　Stageで呼び出し

	// 以下3つ未完成
	virtual void Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* move_vec);	// キャラ同士の当たり判定
	virtual void ClampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able);	// プレイヤー移動時のステージとの当たり判定メソッド
	virtual void draw(VECTOR start, VECTOR end, float radius, int polygon, int dif_color, int spc_color, int flag);
protected:
	int tileHandle;

};

#define CHARA_HIT_HEIGHT		250.f	// 当たり判定カプセルの大きさ
#define CHARA_HIT_WIDTH			50.f	// 当たり判定カプセルの半径
#define CHARA_HIT_PUSH_POWER	20.f	// 