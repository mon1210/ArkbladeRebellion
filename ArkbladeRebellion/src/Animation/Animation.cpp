#include "Animation.h"


// �A�j���[�V�������Z�b�g
void setAnim(int handle, int anim_num, float& anim_timer)
{
    // �^�C�}�[������
    anim_timer = 0.f;
    // �A�j���[�V�������f�^�b�`
    MV1DetachAnim(handle, 0);
    // �A�j���[�V�������A�^�b�`
    MV1AttachAnim(handle, anim_num);

}


// �A�j���[�V�����^�C�}�[��i�s�����A�I���ナ�Z�b�g
bool updateAnimation(float anim_time, float* anim_timer, float anim_f_increment)
{
    if (!anim_timer) { return false; }

    *anim_timer += anim_f_increment;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (*anim_timer >= anim_time)
    {
        *anim_timer = 0.f;
        return true;
    }

    return false;
}