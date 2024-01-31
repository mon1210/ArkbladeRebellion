#include "GlobalFunctions.h"

/**
* @brief  値を指定された範囲内に収めるメソッド
* @param[in] value　範囲内に収める値
* @param[in] min　	最小値
* @param[in] max　	最大値
*/
int clamp(int value, int min, int max)	
{
	if (value < min) 		// 下限
	{
		return min;
	}
	else if (value > max) 	// 上限
	{
		return max;
	}
	else 
	{
		return value;

	}

}


// 値を指定された範囲内に収めるメソッド		
// float用
float clampF(float value, float min, float max)
{
	if (value < min) 		// 下限
	{
		return min;
	}
	else if (value > max) 	// 上限
	{
		return max;
	}
	else
	{
		return value;

	}

}


/**
* @brief  二つのベクトルの外積を求めて返す
* @note	  vec_01とvec_02の外積を求め、VECTOR型を返す
* @param[in] vec_1　一つ目のベクトル
* @param[in] vec_2　二つ目のベクトル
*/
VECTOR cross(VECTOR vec_01, VECTOR vec_02)
{
	VECTOR CrossVec;
	// 外積計算
	CrossVec.x = vec_01.y * vec_02.z - vec_01.z * vec_02.y;
	CrossVec.y = vec_01.z * vec_02.x - vec_01.x * vec_02.z;
	CrossVec.z = vec_01.x * vec_02.y - vec_01.y * vec_02.x;

	return CrossVec;
}