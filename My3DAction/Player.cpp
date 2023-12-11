#include "Player.h"

/**
* @brief Player�̃R���X�g���N�^
*
*/
Player::Player(Game *parent)
{
    animNo = 0;
    animHandle = 0;
    animTime = 0.f;
    animTimer = 0.f;
    hitPoint = 100.f;
    animTimer = 0.f;
    cameraHA = 0.f;
    pCollision = NULL;
    pRadar = NULL;

    angle = PLAYER_START_ROTATE_Y;

    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    newPos = position;
    moveVec = VGet(0.f, 0.f, 0.f);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    pCollision = parent->GetCollision();
    pRadar = parent->GetRadar();

    moveFlag = false;
    rollAble = true;

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, ePlayer::Idle);
}


/**
* @brief �f�X�g���N�^
* @note  �|�C���^��Delete��Stage�ł��Ă���̂ŁA�L�q�̕K�v�Ȃ�
*/
Player::~Player()
{
}


/**
* @brief �v���C���[���f�����Z�b�g����
*
*/
void Player::setPlayerModel(int model)
{
    animHandle = model;
}


/**
* @brief �A�j���[�V�����Z�b�g�֐�
*
*/
void Player::setAnim(ePlayer::AnimationNum num)
{
    if (animNo != num)
    {
        animNo = num;
        animTimer = 0;
        // �A�j���[�V�����ɂ����鎞�Ԃ��擾
        animTime = MV1GetAnimTotalTime(animHandle, animNo);
        // �A�j���[�V�������f�^�b�`
        MV1DetachAnim(animHandle, 0);
        // �A�j���[�V�������A�^�b�`
        MV1AttachAnim(animHandle, animNo);

    }
        animTimer += PLAYER_ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (animTimer >= animTime)
    {
        animTimer -= animTime;
    }
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
}


// Roll�����APLAYER_ANIM_F_INCREMENT(== 0.2f)���ƈ�a��������̂ŁA����Ă���
// �܂��A�������ŉ�]����������̂𒼂��悤�ɂ�������
// ������
void Player::rollAnim()
{
    // �A�j���[�V�������Z�b�g
    if (animNo != ePlayer::Roll)
    {
        animNo = ePlayer::Roll;
        animTimer = 0;
        // �A�j���[�V�����ɂ����鎞�Ԃ��擾
        animTime = MV1GetAnimTotalTime(animHandle, animNo);
        // �A�j���[�V�������f�^�b�`
        MV1DetachAnim(animHandle, 0);
        // �A�j���[�V�������A�^�b�`
        MV1AttachAnim(animHandle, animNo);

    }
    animTimer += PLAYER_ROLL_ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (animTimer >= animTime)
    {
        animTimer -= animTime;
    }
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
}


/**
* @brief �J�����̐����p�x���Z�b�g����
*
*/
void Player::setCameraHAngle(float camera_H_A)
{
    cameraHA = camera_H_A;
}


/**
* @brief �V���W���Z�b�g����
* @note  �ړ���A�V�������W���擾���邽��
*/
void Player::setPlayerNewPos(VECTOR new_pos)
{
    newPos = position;  // ���݂̈ʒu���擾���Ă���
    newPos = new_pos;
}


/**
* @brief �s���Ǘ����\�b�h
*
*/
// ****************************************** //
// PAD���́@PAD_INPUT_1 = ��, PAD_INPUT_2 = �~,
//          PAD_INPUT_3 = �Z, PAD_INPUT_4 = ��,
//          PAD_INPUT_5 = L1, PAD_INPUT_6 = R1,
//          PAD_INPUT_7 = L2, PAD_INPUT_8 = R2,
//          PAD INPUT_9 = SHARE(-),
//          PAD INPUT_10 = OPTIONS(+)
// ****************************************** //
void Player::update()
{
    // �ړ��x�N�g����������
    moveVec = VGet(0.f, 0.f, 0.f);

    // Up => Run���[�V����(3) �O�ړ�
    if (Key_ForwardMove || PadInput & PAD_INPUT_UP)
    {
        // �A�j���[�V�������Z�b�g
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = FORWARD_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.z = PLAYER_MOVE_SPEED;
        }
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        // �A�j���[�V�������Z�b�g
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = BACKWARD_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.z = -PLAYER_MOVE_SPEED;
        }
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        // �A�j���[�V�������Z�b�g
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = RIGHT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = PLAYER_MOVE_SPEED;
        }
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        // �A�j���[�V�������Z�b�g
        setAnim(ePlayer::Run);
        if (animNo == ePlayer::Run)
        {
            angle = LEFT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = -PLAYER_MOVE_SPEED;
        }
    }
    // Space or PAD_�~ => Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_W) && rollAble)
    {
        rollAnim();
        if (animNo == ePlayer::Roll)
        {
            angle = FORWARD_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.z = PLAYER_MOVE_SPEED;
        }
    }
    // �ERoll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_D) && rollAble)
    {
        rollAnim();
        if (animNo == ePlayer::Roll)
        {
            angle = RIGHT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = PLAYER_MOVE_SPEED;
        }
    }
    // ��Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_A) && rollAble)
    {
        rollAnim();
        if (animNo == ePlayer::Roll)
        {
            angle = LEFT_ROTATION_ANGLE - cameraHA;
            moveFlag = true;
            moveVec.x = -PLAYER_MOVE_SPEED;
        }
    }
    // F => Drinking �񕜎����[�V����
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // �A�j���[�V�������Z�b�g
        setAnim(ePlayer::Drinking);
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // �A�j���[�V�������Z�b�g
        setAnim(ePlayer::Dying);
    }
    // Idle
    else
    {
        moveFlag = false;
        setAnim(ePlayer::Idle);
    }

    // �ړ������ꍇ�̓����蔻��X�V�ƍ��W�Z�b�g
    if (moveFlag)
        pCollision->clampToStageBounds(newPos, position, rollAble);

    // Todo �v���C���[�̌����ɑ΂��铮�������܂���
    // ���[�_�[�̒��S�����̍��W�Ɛ��ʂ̌����ɐݒ�
    float rad = angle * (DX_PI / 180.0f);
    float front_vec_x = -sinf(rad);
    float front_vec_z = -cosf(rad);
    VECTOR frontVector = VGet(front_vec_x, 0.0f, front_vec_z);
    pRadar->addCenter(position.x, position.z, frontVector.x, frontVector.z);
}


/**
* @brief �v���C���[�̃A�j���[�V�������\�b�h
* @return true:���� / false:���S
*/
bool Player::move()
{
    if (hitPoint <= 0)
    {
        return false;
    }

    // �V�[���J�ڃf�o�b�O�p
    if (CheckHitKey(KEY_INPUT_O))return false;

    return true;

}


/**
* @brief �`�惁�\�b�h
* @note  �v���C���[��Ǐ]���邽�߃J�����p�֐��͂����ŌĂяo��
*/
void Player::draw()
{
    // ���f���̑傫���ύX
    MV1SetScale(animHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // ���f���̉�]
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // 3D���f���ɍ��W���Z�b�g
    MV1SetPosition(animHandle, position);


    //VECTOR rotate = MV1GetRotationXYZ(anim_handle);
    //int nRotateY = static_cast<int>(rotate.y);
    //DrawFormatString(0, 0, GetColor(0, 0, 0), "nRotateY:%d",nRotateY);


    // 
    //pCollider->draw(position, VAdd(position, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)),
    //    CHARA_HIT_WIDTH, 50, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

    // 3D���f���̕`��
    MV1DrawModel(animHandle);

}


/**
* @brief �v���C���[���W���擾���ĕԂ�
* @note  
*/
VECTOR Player::getPlayerPos()
{   
    return position;
}


/**
* @brief �v���C���[�ړ��x�N�g�����擾���ĕԂ�
* @note
*/
VECTOR Player::getPlayerMoveVec()
{
    return moveVec;
}