/**
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
	//! UIの中心座標X
	float uiCenterX;
	//! UIの中心座標Y
	float uiCenterY;

	//! Radarの中心座標X
	float centerX;
	//! Radarの中心座標Z
	float centerZ;

	//! 正面ベクトルX
	float frontVecX;
	//! 正面ベクトルZ
	float frontVecZ;

	//! Radarの半径
	int raderRadius;
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

	/**
	* @brief RadarPointのデストラクタ
	*/
	~RadarPoint();

	/**
	* @brief 描画メソッド
	* @note  Radarで呼び出し
	* @param[in] param　Radarのパラメータを保存した構造体
	*/
	void draw(RadarData& param);
private:
	//! Pointの座標X
	float posX = 0.f;
	//! Pointの座標Z
	float posZ = 0.f;

	//! 種類
	eRadar::PointType pointType = eRadar::PointType::Default;
};

