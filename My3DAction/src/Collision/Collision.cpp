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
void Collision::initialize(int handle)
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
* @brief  移動時のステージとの当たり判定メソッド
* @note   移動範囲を制限している
* @return true:判定あり、移動可 / false:判定なし、移動不可
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
		return true;
	}
	else
	{
#ifdef _DEBUG
		// 当たらなかった場合は衝突しなかった旨を描画
		DrawString(0, 0, "NO HIT", BLUE);
#endif // !_DEBUG

		return false;
	}

}


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
bool Collision::charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR pos2, float cap1_height, float cap2_height, float cap1_radius, float cap2_radius)
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
			float TempY;		// コピー用

			TempY = NewPos1.y;	// Y軸をコピー
			NewPos1 = VAdd(pos1, VScale(PushVec, cap2_radius * 2.f));

			// Y座標は変化させない
			NewPos1.y = TempY;
			// 当たり判定処理後の移動ベクトルをセット
			pos1_move_vec = VSub(NewPos1, pos1);
		}
		else
		{
			// 押し出し
			NewPos1 = VAdd(NewPos1, VScale(PushVec, CHARA_HIT_PUSH_POWER));
			// 当たり判定処理後の移動ベクトルをセット
			pos1_move_vec = VSub(NewPos1, pos1);
		}

		return true;
	}
	// 当たっていない
	else
	{
		// 当たり判定処理後の移動ベクトルをセット
		pos1_move_vec = VSub(NewPos1, pos1);
		return false;
	}

	return false;
}


/**
* @brief  キャラクターが攻撃範囲内にいるか同かを判定するメソッド
* @note   
* @return true:攻撃範囲の中 / false:攻撃範囲の外
* @param[in] attack_ch_pos　攻撃しようとしているキャラの座標
* @param[in] damage_ch_pos　攻撃を受けようとしているキャラの座標
* @param[in] attack_area　	攻撃範囲
*/
bool Collision::checkAttackArea(VECTOR attack_ch_pos, VECTOR damage_ch_pos, float attack_area)
{
	// 攻撃主から相手までの位置を測る
	float DistanceLength = VSize(VSub(attack_ch_pos, damage_ch_pos));

	// キャラの距離が攻撃範囲より小さかったら
	if (attack_area >= DistanceLength)
	{
		return true;
	}

	return false;
}


/**
* @brief  分離軸候補が、分離軸かどうかを判断
* @note	  OBBの投影距離と二つの距離比較
* 
* @return true:分離軸である / false:分離軸ではない
* @param[in] axis　			分離軸候補
* @param[in] obb1_vertices　一つ目のOBBの頂点
* @param[in] obb2_vertices　二つ目のOBBの頂点
*/
bool Collision::isFindSeparatingAxis(const VECTOR& axis, VECTOR obb1_vertices[8], VECTOR obb2_vertices[8])
{
	// 各OBB頂点リスト
	VECTOR* vertices_list[2] = 
	{
		obb1_vertices,
		obb2_vertices
	};

	// 射影された頂点の最小値と最大値を管理
	struct Length
	{
		float min = 10000.f;	// 大きな値で初期化しないと更新されない
		float max = -10000.f;	// 小さな値で初期化しないと更新されない
	};
	// 2本分
	Length length[2];

	// 2 = vertices_list.size
	for (int i = 0; i < 2; i++)
	{
		// 8 = 各OBBの頂点数
		for (int j = 0; j < 8; j++)
		{
			// [0][0] => [一つ目のOBB][一つ目の頂点]
			VECTOR vertice = vertices_list[i][j];
			// 軸axisと頂点との内積をとる
			// (垂線のベクトル)軸に矩形の頂点を射影して最小、最大を求める
			float dot = axis.x * vertice.x + axis.y * vertice.y + axis.z * vertice.z;

			// 分離軸上で最も遠い頂点までの距離を決める

			// 最小値更新
			if (length[i].min > dot)
			{
				length[i].min = dot;
			}
			// 最大値更新
			if (length[i].max < dot)
			{
				length[i].max = dot;
			}
		}
	}

	// 交差しているとき	分離軸ではない
	if (length[0].min <= length[1].max && length[1].min <= length[0].max)
	{
		return false;
	}

	return true;
}


