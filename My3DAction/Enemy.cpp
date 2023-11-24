/*
* @file	 Enemy.cpp
* @brief
*
*
*/
#include "Enemy.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"


// �R���X�g���N�^
Enemy::Enemy(Stage* pParent)
{
    Parent = pParent;
    anim_no = 0;
    anim_time = 0.f;
    anim_timer = 0.f;
    hitPoint = 1.f;
    angle = ENEMY_START_ROTATE_Y;
    position = VGet(ENEMY_POS_X, ENEMY_POS_Y, ENEMY_POS_Z);

    // �C���X�^���X������
    Model modelObject;
    // ���f���Z�b�g�֐��Ăяo��
    modelObject.EnemyLoadModel();
    anim_handle = modelObject.enemyHandle;

    // 
    MV1AttachAnim(anim_handle, eEnemy::Idle);
    //
    anim_timer = 0.f;
    //
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);

}


// �f�X�g���N�^
Enemy::~Enemy()
{

}


// 
void Enemy::Init()
{

}


// 
void Enemy::SetAnim(void)
{
    // I => Run���[�V����(2)
    if (CheckHitKey(KEY_INPUT_I))
    {
        if (anim_no != eEnemy::Run)
        {
            anim_no = eEnemy::Run;
            anim_timer = 0;
            // �A�j���[�V�����ɂ����鎞�Ԃ��擾
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // �A�j���[�V�������f�^�b�`
            MV1DetachAnim(anim_handle, 0);
            // �A�j���[�V�������A�^�b�`
            MV1AttachAnim(anim_handle, anim_no);
            // ��O�ړ�
            if (anim_no == eEnemy::Run)
            {
                angle = 0.f;
                position.z -= ENEMY_MOVE_SPEED;
            }
        }
    }
    else
    {
        // �A�j���[�V�������Ȃ��Ƃ��AIdle���[�V����(1)
        if (anim_no != eEnemy::Idle)
        {
            anim_no = eEnemy::Idle;
            anim_timer = 0;
            // �A�j���[�V�����ɂ����鎞�Ԃ��擾
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // �A�j���[�V�������f�^�b�`
            MV1DetachAnim(anim_handle, 0);
            // �A�j���[�V�������A�^�b�`
            MV1AttachAnim(anim_handle, anim_no);
        }
    }

}


// 
void Enemy::Update()
{

}


/**
* @brief �G�l�~�[�̃A�j���[�V�������\�b�h
* @return true:���� / false:���S
* @note �����ł͉����x�̐ݒ肾���s���A(x, y)���W�̍X�V��collide() �ōs��
*/
bool Enemy::move()
{
    if (hitPoint <= 0)
    {
        return false;
    }

    return true;

}


/**
* @brief �`�惁�\�b�h
*/
void Enemy::draw()
{
    // 
    SetAnim();

    anim_timer += ENEMY_ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (anim_timer >= anim_time)
    {
        anim_timer = 0.0f;
    }
    MV1SetAttachAnimTime(anim_handle, 0, anim_timer);


    // ��ʂɉf��ʒu��3D���f�����ړ�
    MV1SetPosition(anim_handle, position);

    // ���f���̑傫���ύX
    MV1SetScale(anim_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // ���f���̉�]
    MV1SetRotationXYZ(anim_handle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // �R�c���f���̕`��
    MV1DrawModel(anim_handle);

}