#include "Animation.h"


void SetAnim(int handle, int anim_no, float anim_time, float& anim_timer, float ANIM_F_INCREMENT)
{
    anim_timer = 0;
    // �A�j���[�V�����ɂ����鎞�Ԃ��擾
    anim_time = MV1GetAnimTotalTime(handle, anim_no);
    // �A�j���[�V�������f�^�b�`
    MV1DetachAnim(handle, 0);
    // �A�j���[�V�������A�^�b�`
    MV1AttachAnim(handle, anim_no);

    anim_timer += ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (anim_timer >= anim_time)
    {
        anim_timer = 0.0f;
    }
    MV1SetAttachAnimTime(handle, 0, anim_timer);
}