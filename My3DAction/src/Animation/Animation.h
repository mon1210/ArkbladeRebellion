/*
* @file		Animation.h
* @brief	アニメーションに関するメソッドの定義
*/
#pragma once
#include "DxLib.h"

/**
* @brief アニメーションをセットする
* @param[in] handle         モデルハンドル
* @param[in] anim_num       アニメーションの番号
* @param[in] anim_timer     アニメーションの現在の経過時間
*/
void setAnim(int handle, int anim_num, float& anim_timer);

/**
* @brief   アニメーションタイマーを進行させ、終了後リセットする
* @return  true:アニメーション終了 / false:何もしない
* @param[in] anim_time          アニメーションの総再生時間
* @param[in] anim_timer         アニメーションの現在の経過時間
* @param[in] anim_f_increment   1フレームのアニメーション増加量
*/
bool updateAnimation(float anim_time, float* anim_timer, float anim_f_increment);
