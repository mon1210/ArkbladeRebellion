#include "Animation.h"

/**
* @brief アニメーションをセットする
* @param[in] handle         モデルハンドル
* @param[in] anim_num       アニメーションの番号
* @param[in] anim_timer     アニメーションの現在の経過時間
*/
void setAnim(int handle, int anim_num, float& anim_timer)
{
    // タイマー初期化
    anim_timer = 0.f;
    // アニメーションをデタッチ
    MV1DetachAnim(handle, 0);
    // アニメーションをアタッチ
    MV1AttachAnim(handle, anim_num);

}


/**
* @brief   アニメーションタイマーを進行させ、終了後リセットする
* @return  true:アニメーション終了 / false:何もしない
* @param[in] anim_time          アニメーションの総再生時間
* @param[in] anim_timer         アニメーションの現在の経過時間
* @param[in] ANIM_F_INCREMENT   1フレームのアニメーション増加量
*/
bool updateAnimation(float anim_time, float* anim_timer, float ANIM_F_INCREMENT)
{
    *anim_timer += ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (*anim_timer >= anim_time)
    {
        *anim_timer = 0.f;
        return true;
    }

    return false;
}