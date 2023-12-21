#include "RadarPoint.h"


/**
* @brief RadarPointのコンストラクタ
* @note  posX, posZ, pointTypeは引数で初期化、呼び出し時に値が代入される
* @param[in] x　	x座標
* @param[in] z　	z座標
* @param[in] type_	Pointの種類　何のPoint表しているか
*/
RadarPoint::RadarPoint(float x, float z, eRadar::PointType type_) 
	: posX(x), posZ(z), pointType(type_)
{
}


// デストラクタ
RadarPoint::~RadarPoint()
{
}


/**
* @brief 描画メソッド
* @note  Radarで呼び出し
* @param[in] param　Radarのパラメータを保存した構造体
*/
void RadarPoint::draw(RadarData& param)
{
	// center => Pointの座標でのベクトル
	float centerToPointVecX = posX - param.centerX;
	float centerToPointVecZ = posZ - param.centerZ;

	// ベクトルの長さ
	float vecLength = sqrt(centerToPointVecX * centerToPointVecX + centerToPointVecZ * centerToPointVecZ);

	// 長さが索敵範囲外になったら終了	ここで止まっている
	if (vecLength >= RADAR_DETECTION_RANGE)
		return;

	// pointがcenterに来たら(同じ位置に来たら) 中心にpoint表示
	if (vecLength == 0.f)
	{
		DrawCircle(param.uiCenterX, param.uiCenterY, RADAR_POINT_RADIUS, RED);
		return;
	}


	// center => Pointの座標でのベクトルを正規化
	float normalizedVecX = centerToPointVecX / vecLength;	// X
	float normalizedVecZ = centerToPointVecZ / vecLength;	// Z

	//  center => Pointの単位ベクトルと、frontベクトルの内積(cosθ)を求める
	float dotProduct = normalizedVecX * param.frontVecX + normalizedVecZ * param.frontVecZ;

	// cosθを角度に変更
	float rad = acosf(dotProduct);


	// 左右判定 ------------------------------------------
	//  center => Pointのベクトルと、frontベクトルの外積(yのみ)を求める
	float crossProductY = centerToPointVecX * param.frontVecZ - centerToPointVecZ * param.frontVecX;
	// crossProductYが負の値の時、radを反転
	if (crossProductY < 0.f)
	{
		rad *= -1.f;
	}


	// 角度からベクトルを求める
	float newVecX = sinf(rad);
	float newVecZ = cosf(rad);


	// Raderの索敵範囲と半径の比率を求める
	float rate = param.raderRadius / RADAR_DETECTION_RANGE;


	// 比率にcenter => pointの長さを乗算した値をベクトルの長さにする
	newVecX *= rate * vecLength;
	newVecZ *= rate * vecLength;


	// Point表示
	// 縦軸は上が「-」なので、zの符号を変換
	DrawCircle(param.uiCenterX + newVecX, param.uiCenterY - newVecZ, RADAR_POINT_RADIUS, RED);

}