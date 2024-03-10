#include "Animation.h"


// アニメーションをセット
void setAnim(int handle, int anim_num, float& anim_timer)
{
    // タイマー初期化
    anim_timer = 0.f;
    // アニメーションをデタッチ
    MV1DetachAnim(handle, 0);
    // アニメーションをアタッチ
    MV1AttachAnim(handle, anim_num);

}


// アニメーションタイマーを進行させ、終了後リセット
bool updateAnimation(float anim_time, float* anim_timer, float anim_f_increment)
{
    if (!anim_timer) { return false; }

    *anim_timer += anim_f_increment;
    // アニメーション時間を過ぎたらリセット
    if (*anim_timer >= anim_time)
    {
        *anim_timer = 0.f;
        return true;
    }

    return false;
}