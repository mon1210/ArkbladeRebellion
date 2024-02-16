/*
* @file		RadarPoint.h
* @brief	クラス RadarPoint の宣言
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
	/**
	* @brief RadarPointのコンストラクタ
	* @note  posX, posZ, pointTypeは引数で初期化、呼び出し時に値が代入される
	* @param[in] x　	x座標
	* @param[in] z　	z座標
	* @param[in] type_	Pointの種類　何のPoint表しているか
	*/
	RadarPoint(float x, float z, eRadar::PointType type);

	// デストラクタ
	~RadarPoint();

	/**
	* @brief 描画メソッド
	* @note  Radarで呼び出し
	* @param[in] param　Radarのパラメータを保存した構造体
	*/
	void draw(RadarData& param);
private:
	float posX = 0.f;				// Pointの座標X
	float posZ = 0.f;				// Pointの座標Z

	eRadar::PointType pointType;	// 種類
};

