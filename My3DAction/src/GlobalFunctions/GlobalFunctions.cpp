#include "GlobalFunctions.h"

/**
* @brief  �l���w�肳�ꂽ�͈͓��Ɏ��߂郁�\�b�h
* @param[in] value�@�͈͓��Ɏ��߂�l
* @param[in] min�@	�ŏ��l
* @param[in] max�@	�ő�l
*/
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


/**
* @brief  ��̃x�N�g���̊O�ς����߂ĕԂ�
* @note	  vec_01��vec_02�̊O�ς����߁AVECTOR�^��Ԃ�
* @param[in] vec_1�@��ڂ̃x�N�g��
* @param[in] vec_2�@��ڂ̃x�N�g��
*/
VECTOR cross(VECTOR vec_01, VECTOR vec_02)
{
	VECTOR CrossVec;
	// �O�όv�Z
	CrossVec.x = vec_01.y * vec_02.z - vec_01.z * vec_02.y;
	CrossVec.y = vec_01.z * vec_02.x - vec_01.x * vec_02.z;
	CrossVec.z = vec_01.x * vec_02.y - vec_01.y * vec_02.x;

	return CrossVec;
}