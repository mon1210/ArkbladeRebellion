#include "Radar.h"


// コンストラクタ
Radar::Radar()
{
}


// デストラクタ
Radar::~Radar()
{
}


// 描画メソッド
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


// Pointを追加するメソッド
void Radar::addPoint(float x, float z, eRadar::PointType type_)
{
	// 引数の物から要素を構築
	pointList.emplace_back(x, z, type_);
}


// Radarの中心物体を設定する
void Radar::addCenter(float x, float z, float front_vec_x, float front_vec_z)
{
	centerX = x;
	centerZ = z;

	frontVecX = front_vec_x;
	frontVecZ = front_vec_z;
}


// PointのListを初期化するメソッド
void Radar::listReset()
{
	// リスト内の要素を削除
	pointList.clear();
}