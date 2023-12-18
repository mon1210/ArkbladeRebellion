#include "Radar.h"


/**
* @brief Radarのコンストラクタ
*/
Radar::Radar()
{
}


// デストラクタ
Radar::~Radar()
{
}


/**
* @brief 描画メソッド
*/
void Radar::draw()
{
	// Rader表示
	// UIの円内(黒部分)
	DrawCircle(uiPosX, uiPosY, radius, BLACK, TRUE);
	// UIの円の淵(白線部分)
	DrawCircle(uiPosX, uiPosY, radius, WHITE, FALSE);

	// Radarデータ代入
	RadarData RadarData
	{
		uiPosX,
		uiPosY,
		centerX,
		centerZ,
		frontVecX,
		frontVecZ,
		radius

	};

	// Pointの数分、描画メソッド呼び出し
	for (auto& point : pointList)
	{
		point.draw(RadarData);
	}
}


/**
* @brief Pointを追加するメソッド
* @note  座標取得が必要なので毎フレーム呼び出し
*		 RadarPointのコンストラクタ呼び出し
* @param[in] x　	x座標
* @param[in] z　	z座標
* @param[in] type_	Pointの種類　何のPoint表しているか
*/
void Radar::addPoint(float x, float z, eRadar::PointType type_)
{
	// 引数の物から要素を構築　push_backとほぼ同義
	pointList.emplace_back(x, z, type_);
}


/**
* @brief Radarの中心物体を設定するメソッド
* @note  座標取得が必要なので毎フレーム呼び出し
*		 Playerが中心なのでPlayerで呼び出している
* @param[in] x　			中心物体のx座標
* @param[in] z　			中心物体のz座標
* @param[in] front_vec_x	中心物体の前方ベクトルX
* @param[in] front_vec_z	中心物体の前方ベクトルZ
*/
void Radar::addCenter(float x, float z, float front_vec_x, float front_vec_z)
{
	centerX = x;
	centerZ = z;

	frontVecX = front_vec_x;
	frontVecZ = front_vec_z;
}


/**
* @brief PointのListを初期化するメソッド
* @note  毎フレーム最初に呼び出し
*/
void Radar::listReset()
{
	// リスト内の要素を削除
	pointList.clear();
}