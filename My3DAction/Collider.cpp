#include "Collider.h"

/**
* @brief Cameraのコンストラクタ
*
*/
Collider::Collider()
{
	tileHandle = 0;
}


// デストラクタ
Collider::~Collider()
{
}


/**
* @brief 当たり判定初期化
* @note  床に当たり判定付与
*/
void Collider::InitCollision(int handle)
{
	// Tileに当たり判定付与
	MV1SetupCollInfo(
		handle = 0,			// 当たり判定を設定するモデルのハンドル
		-1,					// 対象となるモデルのフレーム番号(-1は全て)	
		32,					// X軸の空間分割数
		32,					// Y軸の空間分割数
		32					// Z軸の空間分割数
	);
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
		enemy->GetEnemyPos(), VAdd(enemy->GetEnemyPos(), VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH) == TRUE)
	{
		// 当たっていたらプレイヤー押し戻し

		// chk_ch から ch へのベクトルを算出
		ChkChToChVec = VSub(ChPosition, enemy->GetEnemyPos());

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


/**
* @brief 床モデルをセットする
*/
void Collider::setTileModel(int model)
{
	tileHandle = model;
}


/**
* @brief プレイヤー移動時のステージとの当たり判定メソッド
* @note  Playerクラスで呼び出し
*		 プレイヤーの移動範囲を制限している
*/
void Collider::ClampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able)
{
	new_pos.y += 1.0f;  // これがないと左右,下に移動できない
	// MV1_COLL_RESULT_POLY => 当たり判定の結果情報が保存された構造体
	MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
		tileHandle,									    // 判定対象となるモデルのフレーム
		-1,												// 対象となるフレーム番号
		new_pos,										// Rayの始点   モデルの足元
		VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Rayの終点   モデルの頭上
	);

	if (result.HitFlag == 1) // 当たりチェック
	{
		// HitPosition => 交点の座標
		new_pos.y = result.HitPosition.y;
		player_pos = new_pos;
		roll_able = true;
		// 当たったときにその旨を描画
		DrawString(0, 0, "HIT", GetColor(255, 0, 0));
	}
	else
	{
		// ステージ端っこでRollできないように
		roll_able = false;
		// 当たらなかった場合は衝突しなかった旨を描画
		DrawString(0, 0, "NO HIT", GetColor(0, 0, 255));
	}

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