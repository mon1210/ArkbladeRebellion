/*
* @file		Radar.h
* @brief	クラス Radar の宣言
*/
#pragma once
#include "..\RadarPoint\RadarPoint.h"

class Radar
{
public:
	/**
	* @brief Radarのコンストラクタ
	*/
	Radar();

	// デストラクタ
	~Radar();

	/**
	* @brief 描画メソッド
	*/
	void draw();

	/**
	* @brief Pointを追加するメソッド
	* @note  座標取得が必要なので毎フレーム呼び出し
	*		 RadarPointのコンストラクタ呼び出し
	* @param[in] x　	x座標
	* @param[in] z　	z座標
	* @param[in] type_	Pointの種類　何のPoint表しているか
	*/
	void addPoint(float x, float z, eRadar::PointType type);

	/**
	* @brief Radarの中心物体を設定するメソッド
	* @note  座標取得が必要なので毎フレーム呼び出し
	*		 Playerが中心なのでPlayerで呼び出している
	* @param[in] x　			中心物体のx座標
	* @param[in] z　			中心物体のz座標
	* @param[in] front_vec_x	中心物体の前方ベクトルX
	* @param[in] front_vec_z	中心物体の前方ベクトルZ
	*/
	void addCenter(float x, float z, float front_vec_x, float front_vec_z);

	/**
	* @brief PointのListを初期化するメソッド
	* @note  毎フレーム最初に呼び出し
	*/
	void listReset();
private:
	float	uiPosX = 120.f;				// UIの中心座標X
	float	uiPosY = 120.f;				// UIの中心座標Y
	float	centerX = 0.f;				// Radarの中心座標X
	float	centerZ = 0.f;				// Radarの中心座標Z
	float	frontVecX = 0.f;			// 正面ベクトルX
	float	frontVecZ = 0.f;			// 正面ベクトルZ
	float	radius = 100.0f;			// Radarの半径 

	std::vector<RadarPoint> pointList;	// Pointリスト作成
};