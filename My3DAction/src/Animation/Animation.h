/*
* @file		Animation.h
* @brief	アニメーションに関するメソッドの定義
*/
#pragma once
#include "DxLib.h"

// アニメーションをセットする
void setAnim(int handle, int anim_num, float& anim_time, float& anim_timer);

// アニメーションが完了したかを判断する
// true:アニメーションタイマーをリセット / false:何もしない
bool updateAnimation(float anim_time, float* anim_timer, float ANIM_F_INCREMENT);
