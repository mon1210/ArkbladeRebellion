/*
* @file		Animation.h
* @brief	�A�j���[�V�����Ɋւ��郁�\�b�h�̒�`
*/
#pragma once
#include "DxLib.h"

/**
* @brief �A�j���[�V�������Z�b�g����
* @param[in] handle         ���f���n���h��
* @param[in] anim_num       �A�j���[�V�����̔ԍ�
* @param[in] anim_timer     �A�j���[�V�����̌��݂̌o�ߎ���
*/
void setAnim(int handle, int anim_num, float& anim_timer);

/**
* @brief   �A�j���[�V�����^�C�}�[��i�s�����A�I���ナ�Z�b�g����
* @return  true:�A�j���[�V�����I�� / false:�������Ȃ�
* @param[in] anim_time          �A�j���[�V�����̑��Đ�����
* @param[in] anim_timer         �A�j���[�V�����̌��݂̌o�ߎ���
* @param[in] anim_f_increment   1�t���[���̃A�j���[�V����������
*/
bool updateAnimation(float anim_time, float* anim_timer, float anim_f_increment);
