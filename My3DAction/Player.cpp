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
    hitPoint = 0.f;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);

    Model modelObject;
    modelObject.ModelSet();
    anim_handle = modelObject.playerHandle;
    
    // �����ŏ������Ă� -1 �ɂȂ�
    //anim_handle = MV1LoadModel("res\\Player\\PlayerModel.mv1");

    // 
    MV1AttachAnim(anim_handle, ePlayer::Idle);
    //
    anim_timer = 0.f;
    //
    anim_time = MV1GetAnimTotalTime(anim_handle, 0);

}


// �f�X�g���N�^
Player::~Player()
{

}


// 
void Player::Init()
{
    //anim_handle = 0;
    //// 
    //MV1AttachAnim(anim_handle, ePlayer::Idle);
    ////
    //anim_timer = 0.f;
    ////
    //anim_time = MV1GetAnimTotalTime(anim_handle, 0);
}


// 
void Player::SetAnim()
{
    if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_E))
    {
        if (anim_no != ePlayer::Run)
        {
            anim_no = ePlayer::Run;
            anim_timer = 0;
            // �A�j���[�V�����ɂ����鎞�Ԃ��擾
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // �A�j���[�V�������f�^�b�`
            MV1DetachAnim(anim_handle, 0);
            // �A�j���[�V�������A�^�b�`
            MV1AttachAnim(anim_handle, anim_no);
            // 
            if (anim_no == ePlayer::Run)
            {
                angle = -135.f;
                position.x += PLAYER_MOVE_SPEED * VECTOR_SCALING;
                position.z += PLAYER_MOVE_SPEED * VECTOR_SCALING;
            }

        }
    }
    // W or UP => Run���[�V����(3)
    else if (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP))
    {
        if (anim_no != ePlayer::Run)
        {
            //PlayerSetAnimation(player_handle, anim_player_time, player_anim_timer, player_anim_no, PlayerAnimationNum:: PRun);
            anim_no = ePlayer::Run;
            anim_timer = 0;
            // �A�j���[�V�����ɂ����鎞�Ԃ��擾
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // �A�j���[�V�������f�^�b�`
            MV1DetachAnim(anim_handle, 0);
            // �A�j���[�V�������A�^�b�`
            MV1AttachAnim(anim_handle, anim_no);
            // �O�ړ�
            if (anim_no == ePlayer::Run)
            {
                angle = 180.f;
                position.z += PLAYER_MOVE_SPEED;
            }

        }
    }
    // D => Run���[�V����(3) �E�ړ�
    else if (CheckHitKey(KEY_INPUT_D))
    {
        if (anim_no != ePlayer::Run)
        {
            anim_no = ePlayer::Run;
            anim_timer = 0;
            // �A�j���[�V�����ɂ����鎞�Ԃ��擾
            anim_time = MV1GetAnimTotalTime(anim_handle, anim_no);
            // �A�j���[�V�������f�^�b�`
            MV1DetachAnim(anim_handle, 0);
            // �A�j���[�V�������A�^�b�`
            MV1AttachAnim(anim_handle, anim_no);
            // �E�ړ�
            if (anim_no == ePlayer::Run)
            {
                angle = -90.f;
                position.x += PLAYER_MOVE_SPEED;
            }
        }
    }
    else
    {
        // �A�j���[�V�������Ȃ��Ƃ��AIdle���[�V����(4)
        if (anim_no != ePlayer::Idle)
        {
            anim_no = ePlayer::Idle;
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
void Player::Update()
{
    // 
    SetAnim();

    anim_timer += PLAYER_ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (anim_timer >= anim_time)
    {
        anim_time = 0.0f;
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
void Player::draw(ID3D11DeviceContext* pDeviceContext)
{


}

