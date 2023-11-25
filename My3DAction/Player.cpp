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
#include "camera.h"


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
    moveVec = VGet(0.f, 0.f, 0.f);
    anim_timer = 0.f;
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);
    pCamera = new Camera();
    moveFlag = false;

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


// �s���Ǘ��֐�
void Player::SetMove()
{
    // �J��������֐��Ăяo��
    pCamera->CameraController();

    // �ړ��x�N�g����������
    moveVec = VGet(0.f, 0.f, 0.f);

    // Up => Run���[�V����(3) �O�ړ�
    if (CheckHitKey(KEY_INPUT_UP))
    {
        // �A�j���[�V�������Z�b�g
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = 180.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.z = PLAYER_MOVE_SPEED;
        }
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (CheckHitKey(KEY_INPUT_DOWN))
    {
        // �A�j���[�V�������Z�b�g
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = 0.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.z = -PLAYER_MOVE_SPEED;
        }
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        // �A�j���[�V�������Z�b�g
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = -90.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.x = PLAYER_MOVE_SPEED;
        }
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (CheckHitKey(KEY_INPUT_LEFT))
    {
        // �A�j���[�V�������Z�b�g
        SetAnim(ePlayer::Run);
        if (anim_no == ePlayer::Run)
        {
            angle = 90.f - pCamera->CameraHAngle;
            moveFlag = true;
            moveVec.x = -PLAYER_MOVE_SPEED;
        }
    }
    // Space => Roll
    else if (CheckHitKey(KEY_INPUT_SPACE))
    {
        // �A�j���[�V�������Z�b�g
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
        // �A�j���[�V�������Z�b�g
        SetAnim(ePlayer::Drinking);
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // �A�j���[�V�������Z�b�g
        SetAnim(ePlayer::Dying);
    }
    // Idle
    else
    {
        moveFlag = false;
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
* @note  �v���C���[��Ǐ]���邽�߃J�����p�֐��͂����ŌĂяo��
*/
void Player::draw()
{
    // �s���Ǘ��֐��Ăяo��
    SetMove();

    anim_timer += PLAYER_ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (anim_timer >= anim_time)
    {
        anim_timer -= anim_time;
    }
    MV1SetAttachAnimTime(anim_handle, 0, anim_timer);

    // ���f���̑傫���ύX
    MV1SetScale(anim_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // ���f���̉�]
    MV1SetRotationXYZ(anim_handle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // �ړ������ꍇ�A���W�擾
    if (moveFlag)
        position = pCamera->MoveAlongHAngle(moveVec, position);

    // 3D���f���ɍ��W���Z�b�g
    MV1SetPosition(anim_handle, position);

    // �J�����̈ʒu�ƌ�����ݒ�
    pCamera->SetCameraPositionAndDirection(position);

    // �R�c���f���̕`��
    MV1DrawModel(anim_handle);

}

