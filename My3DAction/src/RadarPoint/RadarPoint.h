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
#include "..\Colors.h"
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
	void draw(RadarData& param);	// 描画メソッド　Radar.cppの中で呼び出す
private:
	float posX = 0.f;						// Pointの座標X
	float posZ = 0.f;						// Pointの座標Z

	eRadar::PointType pointType;			// 種類
};

