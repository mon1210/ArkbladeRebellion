/*
* @file		RadarPoint.h
* @brief	クラス RadarPoint の宣言
* @note		
*/
#pragma once
#include <math.h>
#include <DxLib.h>
#include <vector>
#include "..\Enums.h"
#include "..\Constants.h"


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
	virtual void draw(RadarData& param);	// 描画メソッド　Radar.cppの中で呼び出す
private:// Radarで使用できないように
	float posX = 0.f;						// Pointの座標X
	float posZ = 0.f;						// Pointの座標Z
	float centerToPointVecX = 0.f;			// center => point のベクトルX
	float centerToPointVecZ = 0.f;			// center => point のベクトルZ
	float vecLength = 0.f;					// ベクトルの長さ
	float normalizedVecX = 0.f;				// 正規化後ベクトルX
	float normalizedVecZ = 0.f;				// 正規化後ベクトルZ
	float rad = 0.f;						// 弧度法(radian)の度数
	float dotProduct = 0.f;					// ベクトルの内積
	float crossProductY = 0.f;				// ベクトルの外積
	float newVecX = 0.f;					// 角度を求めた後のベクトルX
	float newVecZ = 0.f;					// 角度を求めた後のベクトルZ
	float rate = 0.f;						// Raderの索敵範囲と半径の比率

	eRadar::PointType pointType;			// 種類
};

#define RED	GetColor(255, 0, 0)