#include "Animation.h"


void SetAnim(int handle, int anim_no, float anim_time, float& anim_timer, float ANIM_F_INCREMENT)
{
    anim_timer = 0;
    // アニメーションにかかる時間を取得
    anim_time = MV1GetAnimTotalTime(handle, anim_no);
    // アニメーションをデタッチ
    MV1DetachAnim(handle, 0);
    // アニメーションをアタッチ
    MV1AttachAnim(handle, anim_no);

    anim_timer += ANIM_F_INCREMENT;
    // アニメーション時間を過ぎたらリセット
    if (anim_timer >= anim_time)
    {
        anim_timer = 0.0f;
    }
    MV1SetAttachAnimTime(handle, 0, anim_timer);
}