#include "Collision.h"

/**
* @brief Collisionのコンストラクタ
*/
Collision::Collision(Game *Game_)
{
	pGame = Game_;

	if (pGame)
		tileHandle = pGame->GetBG()->GetModelHandle();
}


// デストラクタ
Collision::~Collision()
{
}


/**
* @brief 当たり判定初期化
* @note  床に当たり判定付与
*/
void Collision::initCollision(int handle)
{
	// Tileに当たり判定付与
	MV1SetupCollInfo(
		handle = 0,		// 当たり判定を設定するモデルのハンドル
		-1,					// 対象となるモデルのフレーム番号(-1は全て)	
		SPATIAL_PARTITION,	// X軸の空間分割数
		SPATIAL_PARTITION,	// Y軸の空間分割数
		SPATIAL_PARTITION	// Z軸の空間分割数
	);
}


/**
* @brief 移動時のステージとの当たり判定メソッド
* @note  移動範囲を制限している
*/
bool Collision::clampToStageBounds(VECTOR& new_pos, VECTOR& pos)
{
	new_pos.y += 1.0f;  // これがないと左右,下に移動できない
	// MV1_COLL_RESULT_POLY => 当たり判定の結果情報が保存された構造体
	MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(
		tileHandle,												// 判定対象となるモデルのフレーム
		-1,														// 対象となるフレーム番号
		new_pos,												// Rayの始点   モデルの足元
		VGet(new_pos.x, new_pos.y - CHARA_HEIGHT, new_pos.z)	// Rayの終点   モデルの頭上
	);

	if (Result.HitFlag == 1) // 当たりチェック
	{
		// HitPosition => 交点の座標
		new_pos.y = Result.HitPosition.y;
		pos = new_pos;
		// 当たったときにその旨を描画
		DrawString(0, 0, "HIT", GetColor(255, 0, 0));
		return true;
	}
	else
	{
		// 当たらなかった場合は衝突しなかった旨を描画
		DrawString(0, 0, "NO HIT", GetColor(0, 0, 255));
		return false;
	}

}


/**
* @brief キャラ同士のカプセル当たり判定メソッド
* @note  playerの移動時に呼び出している
* @param[in] pos1　			移動しているキャラの座標
* @param[in] pos1_move_vec　移動しているキャラの移動ベクトル
* @param[in] pos2　			当たられる側の座標
* @param[in] cap1_height　	pos1のカプセルの高さ
* @param[in] cap2_height　	pos2のカプセルの高さ
* @param[in] cap1_radius　	pos1のカプセルの半径
* @param[in] cap2_radius　	pos2のカプセルの半径
*/
void Collision::charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR& pos2, float cap1_height, float cap2_height, float cap1_radius, float cap2_radius)
{
	// 移動後の ch の座標を算出
	VECTOR NewPos1 = VAdd(pos1, pos1_move_vec);

	// 二つのカプセルで当たり判定
	if (HitCheck_Capsule_Capsule(
		pos1, VGet(pos1.x, pos1.y + cap1_height, pos1.z), cap1_radius,
		pos2, VGet(pos2.x, pos2.y + cap2_height, pos2.z), cap2_radius) == TRUE)
	{
		// pos2 から pos1 へのベクトルを算出
		VECTOR Pos2ToPos1Vec = VSub(NewPos1, pos2);

		// Ｙ軸は見ない
		Pos2ToPos1Vec.y = 0.f;

		// 二人の距離を算出
		float Length = VSize(Pos2ToPos1Vec);

		// pos2 から pos1 へのベクトルを正規化( ベクトルの長さを 1.0f にする )
		VECTOR PushVec = VScale(Pos2ToPos1Vec, 1.f / Length);

		// 押し出す距離を算出 ------
		// 二人の距離から二人の大きさを引いた値に押し出し力を足しても離れてしまう場合は、ぴったりくっつく距離に移動する
		if (Length - (cap2_radius * 2.f) + CHARA_HIT_PUSH_POWER > 0.f)	// * 2.f => 直径を求める
		{
			float TempY;	// コピー用

			TempY = NewPos1.y;	// Y軸をコピー
			NewPos1 = VAdd(pos1, VScale(PushVec, cap2_radius * 2.f));

			// Y座標は変化させない
			NewPos1.y = TempY;

		}
		else
		{
			// 押し出し
			NewPos1 = VAdd(NewPos1, VScale(PushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// 当たり判定処理後の移動ベクトルをセット
	pos1_move_vec = VSub(NewPos1, pos1);

}