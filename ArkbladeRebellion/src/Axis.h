/**
* @file		Axis.h
* @brief	Axis�\���� �̐錾
* @note		OBB�̎��ۑ��p
*/
#pragma once
#include "DxLib.h"

struct Axis
{
	VECTOR x = VGet(0.f, 0.f, 0.f);
	VECTOR y = VGet(0.f, 0.f, 0.f);
	VECTOR z = VGet(0.f, 0.f, 0.f);
};