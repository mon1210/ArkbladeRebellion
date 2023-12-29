/*
* @file		Radar.h
* @brief	クラス Radar の宣言
* @note
*/
#pragma once
#include "..\RadarPoint\RadarPoint.h"

class Radar
{
public:
	Radar();
	~Radar();
	void draw();															// 描画メソッド
	void addPoint(float x, float z, eRadar::PointType type);				// Pointを追加するメソッド
	void addCenter(float x, float z, float front_vec_x, float front_vec_z);	// Radarの中心物体を設定するメソッド
	void listReset();														// PointのListを初期化するメソッド	毎フレーム最初に呼び出し
protected:
	float	uiPosX = 120.f;				// UIの中心座標X
	float	uiPosY = 120.f;				// UIの中心座標Y
	float	centerX = 0.f;				// Radarの中心座標X
	float	centerZ = 0.f;				// Radarの中心座標Z
	float	frontVecX = 0.f;			// 正面ベクトルX
	float	frontVecZ = 0.f;			// 正面ベクトルZ
	float	radius = 100.0f;			// Radarの半径 

	std::vector<RadarPoint> pointList;	// Pointリスト作成
};