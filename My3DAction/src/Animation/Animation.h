/*
* @file		Animation.h
* @brief	�A�j���[�V�����Ɋւ��郁�\�b�h�̒�`
*/
#pragma once
#include "DxLib.h"

// �A�j���[�V�������Z�b�g����
void setAnim(int handle, int anim_num, float& anim_time, float& anim_timer);

// �A�j���[�V�����������������𔻒f����
// true:�A�j���[�V�����^�C�}�[�����Z�b�g / false:�������Ȃ�
bool updateAnimation(float anim_time, float* anim_timer, float ANIM_F_INCREMENT);
