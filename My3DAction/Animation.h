/*
* @file		Animation.h
* @brief	�A�j���[�V�����Ɋւ��郁�\�b�h�̒�`
*/
#pragma once
#include "DxLib.h"

/*---------------------------------------------------------------*
 * @param[in] handle			 ���f���n���h��					 *
 * @param[in] anim_no			 �A�j���[�V�����̔ԍ�			 *
 * @param[in] anim_timer		 �A�j���[�V�����̌��݂̌o�ߎ���	 *
 * @param[in] anim_time			 �A�j���[�V�����̑��Đ�����		 *
 * @param[in] ANIM_F_INCREMENT   1�t���[���̃A�j���[�V���������� *
 *---------------------------------------------------------------*/

// �A�j���[�V�������Z�b�g����
void SetAnim(int handle, int anim_no, float& anim_time, float& anim_timer);

// �A�j���[�V�����������������𔻒f����
// return  true:�A�j���[�V�����^�C�}�[�����Z�b�g / false:�������Ȃ�
bool IsAnimationComplete(float anim_time, float& anim_timer, float ANIM_F_INCREMENT);
