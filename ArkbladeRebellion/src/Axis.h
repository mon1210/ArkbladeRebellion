/**
* @file		Axis.h
* @brief	Axis構造体 の宣言
* @note		OBBの軸保存用
*/
#pragma once
#include "DxLib.h"

struct Axis
{
	VECTOR x = VGet(0.f, 0.f, 0.f);
	VECTOR y = VGet(0.f, 0.f, 0.f);
	VECTOR z = VGet(0.f, 0.f, 0.f);
};