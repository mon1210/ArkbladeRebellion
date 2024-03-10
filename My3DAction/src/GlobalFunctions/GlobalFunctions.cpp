#include "GlobalFunctions.h"


// 値を指定された範囲内に収める
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


// 値を指定された範囲内に収めるメソッド	 float用
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


// 二つのベクトルの外積を求めて返す
VECTOR cross(VECTOR vec_01, VECTOR vec_02)
{
	VECTOR CrossVec;
	// 外積計算
	CrossVec.x = vec_01.y * vec_02.z - vec_01.z * vec_02.y;
	CrossVec.y = vec_01.z * vec_02.x - vec_01.x * vec_02.z;
	CrossVec.z = vec_01.x * vec_02.y - vec_01.y * vec_02.x;

	return CrossVec;
}