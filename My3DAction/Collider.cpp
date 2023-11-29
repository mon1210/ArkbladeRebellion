#include "Collider.h"
#include "Player.h"
#include "Enemy.h"


/**
* @brief Cameraのコンストラクタ
*
*/
Collider::Collider()
{

}


// デストラクタが
Collider::~Collider()
{

}


// キャラ同士の当たり判定
void Collider::Chara_Collision(Player* player, Enemy* enemy)
{
	VECTOR ChkChToChVec;
	VECTOR PushVec;
	float Length;

	// 
	if (HitCheck_Capsule_Capsule(
		player->position, VAdd(player->position, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH,
		enemy->position, VAdd(enemy->position, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH) == TRUE)
	{
		// 当たっていたらプレイヤー押し戻し

		// chk_ch から ch へのベクトルを算出
		ChkChToChVec = VSub(player->position, enemy->position);

		// Ｙ軸は見ない
		ChkChToChVec.y = 0.f;

		// 二人の距離を算出
		Length = VSize(ChkChToChVec);

		// chk_ch から ch へのベクトルを正規化( ベクトルの長さを 1.0f にする )
		PushVec = VScale(ChkChToChVec, 1.0f / Length);

		// 押し出す距離を算出、もし二人の距離から二人の大きさを引いた値に押し出し力を足して離れてしまう場合は、ぴったりくっつく距離に移動する
		if (Length - CHARA_HIT_WIDTH * 2.0f + CHARA_HIT_PUSH_POWER > 0.0f)
		{
			float TempY;

			TempY = player->position.y;
			player->position = VAdd(player->position, VScale(PushVec, CHARA_HIT_WIDTH * 2.0f));

			// Ｙ座標は変化させない
			player->position.y = TempY;
		}
		else
		{
			// 押し出し
			player->position = VAdd(player->position, VScale(PushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// 当たり判定処理後の移動ベクトルをセット
	// *ch_MoveVec = VSub(player->position, ch->Position);


}



// 
void Collider::draw()
{

}