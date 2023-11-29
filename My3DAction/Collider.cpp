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
void Collider::Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* moveVec)
{
	VECTOR ChkChToChVec;
	VECTOR PushVec;
	VECTOR ChPosition;
	float Length;

	// 移動後の ch の座標を算出
	ChPosition = VAdd(*player, *moveVec);

	// 
	if (HitCheck_Capsule_Capsule(
		ChPosition, VAdd(ChPosition, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH,
		enemy->position, VAdd(enemy->position, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH) == TRUE)
	{
		// 当たっていたらプレイヤー押し戻し

		// chk_ch から ch へのベクトルを算出
		ChkChToChVec = VSub(ChPosition, enemy->position);

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

			TempY = ChPosition.y;
			ChPosition = VAdd(*player, VScale(PushVec, CHARA_HIT_WIDTH * 2.0f));

			// Ｙ座標は変化させない
			ChPosition.y = TempY;
		}
		else
		{
			// 押し出し
			ChPosition = VAdd(ChPosition, VScale(PushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// 当たり判定処理後の移動ベクトルをセット
	*moveVec = VSub(ChPosition, *player);


}



// 
void Collider::draw(VECTOR start, VECTOR end, float radius, int polygon, int difColor, int spcColor, int flag)
{

	VECTOR dir = VSub(end, start);
	float length = VSize(dir);

	// カプセル中心線
	DrawLine3D(start, end, difColor);

	// 座標 ( 320.0f, 100.0f, 0.0f ) と ( 320.0f, 300.0f, 0.0f ) を２点とする
    // 半径 40.0f のカプセルを描画する
	// DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(255, 255, 0), FALSE);
	
	// カプセルの上半分
	DrawCapsule3D(start, VGet(length / 2, 0.f, 0.f), radius, polygon, difColor, spcColor, flag);

	// カプセルの下半分
	DrawCapsule3D(end, VGet(length / 2, 0.f, 0.f), radius, polygon, difColor, spcColor, flag);

}