/*
* @file		Animation.h
* @brief	アニメーションに関するメソッドの定義
*/
#pragma once
#include "DxLib.h"

/*---------------------------------------------------------------*
 * @param[in] handle			 モデルハンドル					 *
 * @param[in] anim_no			 アニメーションの番号			 *
 * @param[in] anim_timer		 アニメーションの現在の経過時間	 *
 * @param[in] anim_time			 アニメーションの総再生時間		 *
 * @param[in] ANIM_F_INCREMENT   1フレームのアニメーション増加量 *
 *---------------------------------------------------------------*/

// アニメーションをセットする
void SetAnim(int handle, int anim_no, float& anim_time, float& anim_timer);

// アニメーションが完了したかを判断する
// return  true:アニメーションタイマーをリセット / false:何もしない
bool IsAnimationComplete(float anim_time, float& anim_timer, float ANIM_F_INCREMENT);
