#include "GlobalFunctions.h"

// 値を指定された範囲内に収めるメソッド
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