#include "GlobalFunctions.h"

// �l���w�肳�ꂽ�͈͓��Ɏ��߂郁�\�b�h
int clamp(int value, int min, int max)	
{
	if (value < min) 		// ����
	{
		return min;
	}
	else if (value > max) 	// ���
	{
		return max;
	}
	else 
	{
		return value;

	}

}


// �l���w�肳�ꂽ�͈͓��Ɏ��߂郁�\�b�h		
// float�p
float clampF(float value, float min, float max)
{
	if (value < min) 		// ����
	{
		return min;
	}
	else if (value > max) 	// ���
	{
		return max;
	}
	else
	{
		return value;

	}

}