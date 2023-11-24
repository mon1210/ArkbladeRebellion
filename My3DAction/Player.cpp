/*
* @file	 Player.cpp
* @brief
*
*
*/
#include "Player.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"


// �R���X�g���N�^
Player::Player(Stage* pParent)
{
    Parent = pParent;
    anim_no = 0;
    anim_time = 0.f;
    anim_timer = 0.f;
    hitPoint = 100.f;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);
    anim_timer = 0.f;
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);

    // �C���X�^���X������
    Model modelObject;
    // ���f���Z�b�g�֐��Ăяo��
    modelObject.PlayerLoadModel();
    anim_handle = modelObject.playerHandle;

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(anim_handle, ePlayer::Idle);

}


// �f�X�g���N�^
Player::~Player()
{

}


// 
void Player::Init()
{

}



// �A�j���[�V�����Z�b�g�֐�
void Player::SetAnim(ePlayer::AnimationNum num)
{
    if (anim_no != num)
    {
        anim_no = num;
        anim_timer = 0;
        // �A�j���[�V�����ɂ����鎞�Ԃ��擾
        anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
        // �A�j���[�V�������f�^�b�`
        MV1DetachAnim(anim_handle, 0);
        // �A�j���[�V�������A�^�b�`
        MV1AttachAnim(anim_handle, anim_no);

    }
}


// 
void Player::SetMove()
{
    if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_E))
    {
        // 
        SetAnim(ePlayer::Run);
        // 
        if (anim_no == ePlayer::Run)
        {
            angle = -135.f;
            position.x += PLAYER_MOVE_SPEED * VECTOR_SCALING;
            position.z += PLAYER_MOVE_SPEED * VECTOR_SCALING;
        }
    }
    // W or UP => Run���[�V����(3)
    else if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP))
    {
        // 
        SetAnim(ePlayer::Run);
        // �O�ړ�
        if (anim_no == ePlayer::Run)
        {
            angle = 180.f;
            position.z += PLAYER_MOVE_SPEED;
        }

    }
    // D => Run���[�V����(3) �E�ړ�
    else if (CheckHitKey(KEY_INPUT_D))
    {
        // 
        SetAnim(ePlayer::Run);
        // �E�ړ�
        if (anim_no == ePlayer::Run)
        {
            angle = -90.f;
            position.x += PLAYER_MOVE_SPEED;
        }
    }
    // Space => Roll
    else if (CheckHitKey(KEY_INPUT_SPACE))
    {
        // 
        SetAnim(ePlayer::Roll);
        // �E�ړ�
        if (anim_no == ePlayer::Roll)
        {
            position.z += 0.5f; // ���̂܂܂��Ɖ������ł�Z�����ɐi��ł��܂�  Todo
        }
    }
    // F => Drinking �񕜎����[�V����
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // 
        SetAnim(ePlayer::Drinking);
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // 
        SetAnim(ePlayer::Dying);
    }
    // Idle
    else
    {
        SetAnim(ePlayer::Idle);
    }


}


// 
void Player::Update()
{
 
}


/**
* @brief �v���C���[�̃A�j���[�V�������\�b�h
* @return true:���� / false:���S
* @note �����ł͉����x�̐ݒ肾���s���A(x, y)���W�̍X�V��collide() �ōs��
*/
bool Player::move()
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
void Player::draw()
{
    // �A�j���[�V�����Ăяo���֐�
    SetMove();

    anim_timer += PLAYER_ANIM_F_INCREMENT;
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

