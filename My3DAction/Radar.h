/*
* @file		Radar.h
* @brief	クラス Radar の宣言
* @note
*/
#pragma once
#include "RadarPoint.h"

class Radar
{
public:
	Radar();
	~Radar();
	virtual void draw();	// 描画メソッド
	virtual void addPoint(float x, float z, eRadar::PointType type);	// Pointを追加するメソッド
	virtual void addCenter(float x, float z, float front_vec_x, float front_vec_z);	// Radarの中心物体を設定するメソッド
	virtual void listReset();	// PointのListを初期化するメソッド	毎フレーム最初に呼び出し
protected:
	float	uiPosX;		// UIの中心座標X
	float	uiPosY;		// UIの中心座標Y
	float	centerX;	// Radarの中心座標X
	float	centerZ;	// Radarの中心座標Z
	float	frontVecX;	// 正面ベクトルX
	float	frontVecZ;	// 正面ベクトルZ
	float	radius;		// Radarの半径 
	std::vector<RadarPoint> pointList;	// Pointリスト作成
};

#define WHITE GetColor(255, 255, 255)
#define BLACK GetColor(0, 0, 0)