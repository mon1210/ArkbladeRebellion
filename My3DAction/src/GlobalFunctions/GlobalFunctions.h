/**
* @file		GlobalFunctions.h
* @brief	�O���[�o���֐��̐錾
*/
#pragma once
#include "DxLib.h"

/**
* @brief  �l���w�肳�ꂽ�͈͓��Ɏ��߂郁�\�b�h
* @param[in] value�@�͈͓��Ɏ��߂�l
* @param[in] min�@	�ŏ��l
* @param[in] max�@	�ő�l
*/
int clamp(int value, int min, int max);
// float�p
float clampF(float value, float min, float max);

/**
* @brief  ��̃x�N�g���̊O�ς����߂ĕԂ�
* @note	  vec_01��vec_02�̊O�ς����߁AVECTOR�^��Ԃ�
* @param[in] vec_1�@��ڂ̃x�N�g��
* @param[in] vec_2�@��ڂ̃x�N�g��
*/
VECTOR cross(VECTOR vec_01, VECTOR vec_02);