/*
* @file		RadarPoint.h
* @brief	クラス RadarPoint の宣言
* @note		
*/
#pragma once
#include <math.h>
#include <DxLib.h>
#include <vector>
#include "Enums.h"
#include "Constants.h"


// Radarクラスで中身代入、このクラスで使用
struct RadarData
{
	float uiCenterX;	// UIの中心座標(XY)
	float uiCenterY;

	float centerX;		// Radarの中心座標(XZ)
	float centerZ;

	float frontVecX;	// 正面ベクトル(XZ)
	float frontVecZ;

	float raderRadius;	// Radarの半径
};


class RadarPoint
{
public:
	RadarPoint(float x, float z, eRadar::PointType type_);
	~RadarPoint();
	virtual void Draw(RadarData& param);	// 描画メソッド　Radar.cppの中で呼び出す
private:	// Radarで使用できないように
	float posX;	// Pointの座標
	float posZ;
	float centerToPointVecX;	// center => point のベクトルX
	float centerToPointVecZ;	// center => point のベクトルZ
	float vecLength;			// ベクトルの長さ
	float normalizedVecX;		// 正規化後ベクトルX
	float normalizedVecZ;		// 正規化後ベクトルZ
	float rad;					// 弧度法(radian)の度数
	float dotProduct;			// ベクトルの内積
	float crossProductY;		// ベクトルの外積
	float newVecX;				// 角度を求めた後のベクトルX
	float newVecZ;				// 角度を求めた後のベクトルZ
	float rate;					// Raderの索敵範囲と半径の比率

	eRadar::PointType pointType;
};

#define RED	GetColor(255, 0, 0)