#include "Animation.h"

/**
* @brief �A�j���[�V�������Z�b�g����
* @param[in] handle         ���f���n���h��
* @param[in] anim_no        �A�j���[�V�����̔ԍ�
* @param[in] anim_timer     �A�j���[�V�����̌��݂̌o�ߎ���
* @param[in] anim_time      �A�j���[�V�����̑��Đ�����
*/
void setAnim(int handle, int anim_no, float& anim_time, float& anim_timer)
{
    // �^�C�}�[������
    anim_timer = 0.f;
    // �A�j���[�V�����ɂ����鎞�Ԃ��擾
    anim_time = MV1GetAnimTotalTime(handle, anim_no);
    // �A�j���[�V�������f�^�b�`
    MV1DetachAnim(handle, 0);
    // �A�j���[�V�������A�^�b�`
    MV1AttachAnim(handle, anim_no);

}

/**
* @brief   �A�j���[�V�����������������𔻒f����
* @return  true:�A�j���[�V�����^�C�}�[�����Z�b�g / false:�������Ȃ�
* @param[in] anim_time          �A�j���[�V�����̑��Đ�����
* @param[in] anim_timer         �A�j���[�V�����̌��݂̌o�ߎ���
* @param[in] ANIM_F_INCREMENT   1�t���[���̃A�j���[�V����������
*/
bool isAnimationComplete(float anim_time, float& anim_timer, float ANIM_F_INCREMENT)
{
    anim_timer += ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (anim_timer >= anim_time)
    {
        return true;
    }

    return false;
}