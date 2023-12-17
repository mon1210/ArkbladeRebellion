#include "Collision.h"

/**
* @brief Collisionのコンストラクタ
*/
Collision::Collision(Game *Game_)
{
	pGame = Game_;

	if (pGame)
		tileHandle = pGame->GetModelManager()->getTileModel();

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
		handle = 0,			// 当たり判定を設定するモデルのハンドル
		-1,					// 対象となるモデルのフレーム番号(-1は全て)	
		SPATIAL_PARTITION,	// X軸の空間分割数
		SPATIAL_PARTITION,	// Y軸の空間分割数
		SPATIAL_PARTITION	// Z軸の空間分割数
	);
}


/**
* @brief プレイヤー移動時のステージとの当たり判定メソッド
* @note  Playerクラスで呼び出し
*		 プレイヤーの移動範囲を制限している
*/
void Collision::clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able)
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


/**
* @brief デバッグ用　キャラ同士のカプセル描画メソッド
* @note  Gameで毎フレーム呼び出している
*/
void Collision::debugCapColDraw()
{
	// player
	VECTOR Pos = pGame->GetPlayer()->getPos();
	DrawCapsule3D(Pos, VGet(Pos.x, Pos.y + CAP_HEIGHT, Pos.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);
	// enemy
	VECTOR ePos = pGame->GetEnemy()->getPos();
	DrawCapsule3D(ePos, VGet(ePos.x, ePos.y + CAP_HEIGHT, ePos.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
}


/**
* @brief キャラ同士のカプセル当たり判定メソッド
* @note  playerの移動時に呼び出している
* @param[in] pos1　			移動しているキャラの座標
* @param[in] pos1_move_vec　移動しているキャラの移動ベクトル
* @param[in] pos2　			当たられる側の座標
* @param[in] CAP1_HEIGHT　	pos1のカプセルの高さ
* @param[in] CAP2_HEIGHT　	pos2のカプセルの高さ
* @param[in] CAP1_RADIUS　	pos1のカプセルの半径
* @param[in] CAP2_RADIUS　	pos2のカプセルの半径
*/
void Collision::charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR& pos2, float CAP1_HEIGHT, float CAP2_HEIGHT, float CAP1_RADIUS, float CAP2_RADIUS)
{

	// 移動後の ch の座標を算出
	VECTOR NewPos1 = VAdd(pos1, pos1_move_vec);

	// 二つのカプセルで当たり判定
	if (HitCheck_Capsule_Capsule(
		pos1, VGet(pos1.x, pos1.y + CAP1_HEIGHT, pos1.z), CAP1_RADIUS,
		pos2, VGet(pos2.x, pos2.y + CAP2_HEIGHT, pos2.z), CAP2_RADIUS) == TRUE)
	{
		// pos2 から pos1 へのベクトルを算出
		VECTOR Pos2ToPos1Vec = VSub(NewPos1, pos2);

		// Ｙ軸は見ない
		Pos2ToPos1Vec.y = 0.f;

		// 二人の距離を算出
		float length = VSize(Pos2ToPos1Vec);

		// pos2 から pos1 へのベクトルを正規化( ベクトルの長さを 1.0f にする )
		VECTOR pushVec = VScale(Pos2ToPos1Vec, 1.f / length);

		// 押し出す距離を算出 ------
		// 二人の距離から二人の大きさを引いた値に押し出し力を足しても離れてしまう場合は、ぴったりくっつく距離に移動する
		if (length - (CAP2_RADIUS * 2.f) + CHARA_HIT_PUSH_POWER > 0.f)	// * 2.f => 直径を求める
		{
			float TempY;	// コピー用

			TempY = NewPos1.y;	// Y軸をコピー
			NewPos1 = VAdd(pos1, VScale(pushVec, CAP2_RADIUS * 2.f));

			// Y座標は変化させない
			NewPos1.y = TempY;

		}
		else
		{
			// 押し出し
			NewPos1 = VAdd(NewPos1, VScale(pushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// 当たり判定処理後の移動ベクトルをセット
	pos1_move_vec = VSub(NewPos1, pos1);

}