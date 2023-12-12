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


// Roll�����APLAYER_ANIM_F_INCREMENT(== 0.2f)���ƈ�a��������̂ŁA����Ă���
// �܂��A�������ŉ�]����������̂𒼂��悤�ɂ�������
// ������


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
* @brief �ړ����̍s���Ǘ�
* @note  �A�j���[�V�����ƌ����̐ݒ������
*        moveFlag�͂�����true��
* @param[in] num�@	        �A�j���[�V�����ԍ�
* @param[in] ROTATE_ANGLE�@	��]�p�x
* @param[in] move_x�@	    x�������̈ړ��X�s�[�h
* @param[in] move_z�@	    z�������̈ړ��X�s�[�h
*/
void Player::moveHandle(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z)
{
    // �A�j���[�V�������Z�b�g
    if (animNo != num)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNo = num;
        SetAnim(animHandle, animNo, animTime, animTimer);
    }

    // �ړ���������Ƒ��x��ݒ�
    if (animNo == num)
    {
        angle = ROTATE_ANGLE - cameraHA;
        moveFlag = true;
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


/**
* @brief �s���Ǘ����\�b�h
* @note  ���͂��ꂽ�L�[�ɂ���čs������
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
        // �A�j���[�V�����A�ړ�������Z�b�g
        moveHandle(ePlayer::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // �A�j���[�V�����^�C�}�[���Z�b�g
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        moveHandle(ePlayer::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        moveHandle(ePlayer::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        moveHandle(ePlayer::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Space or PAD_�~ => Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_W) && rollAble)
    {
        moveHandle(ePlayer::Roll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // �ERoll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_D) && rollAble)
    {
        moveHandle(ePlayer::Roll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // ��Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_A) && rollAble)
    {
        moveHandle(ePlayer::Roll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // F => Drinking �񕜎����[�V����
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // angle ���Z�b�g���邱�Ƃō��̌�����ێ�
        moveHandle(ePlayer::Drinking, angle, 0, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        moveHandle(ePlayer::Dying, angle, 0, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Idle
    else
    {
        moveFlag = false;
        moveHandle(ePlayer::Idle,angle, 0, 0);
        if (IsAnimationComplete(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }

    // ���f���Ƀ^�C�}�[�Z�b�g
    // ���ꂪ�Ȃ��ƃA�j���[�V�������Ȃ�
    MV1SetAttachAnimTime(animHandle, 0, animTimer);

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