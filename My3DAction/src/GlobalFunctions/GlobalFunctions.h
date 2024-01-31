/**
* @file		GlobalFunctions.h
* @brief	グローバル関数の宣言
*/
#pragma once
#include "DxLib.h"

/**
* @brief  値を指定された範囲内に収めるメソッド
* @param[in] value　範囲内に収める値
* @param[in] min　	最小値
* @param[in] max　	最大値
*/
int clamp(int value, int min, int max);
// float用
float clampF(float value, float min, float max);

/**
* @brief  二つのベクトルの外積を求めて返す
* @note	  vec_01とvec_02の外積を求め、VECTOR型を返す
* @param[in] vec_1　一つ目のベクトル
* @param[in] vec_2　二つ目のベクトル
*/
VECTOR cross(VECTOR vec_01, VECTOR vec_02);