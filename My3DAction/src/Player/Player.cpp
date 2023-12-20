#include "Player.h"

/**
* @brief Player�̃R���X�g���N�^
*/
Player::Player(Game *Game_)
{
    hitPoint = MAX_HP;

    pGame = Game_;
    
    // ���f���擾
    if (pGame)
        animHandle = pGame->GetModelManager()->GetPlayerModel();

    angle = PLAYER_START_ROTATE_Y;

    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, ePlayer::Idle);
}


/**
* @brief �f�X�g���N�^
* @note  �|�C���^��Delete��Game�N���X�ł��Ă���̂ŁA�L�q�̕K�v�Ȃ�
*/
Player::~Player()
{
}


// Roll���A�������ŉ�]����������̂𒼂��悤�ɂ�������
// Todo
// void RollHandle(){}


/**
* @brief �ړ����̍s���Ǘ�
* @note  �A�j���[�V�����ƌ����̐ݒ������
*        moveFlag�͂�����true��
* @param[in] num�@	        �A�j���[�V�����ԍ�
* @param[in] ROTATE_ANGLE�@	��]�p�x
* @param[in] move_x�@	    x�������̈ړ��X�s�[�h
* @param[in] move_z�@	    z�������̈ړ��X�s�[�h
*/
void Player::animateAndMove(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z)
{
    // �A�j���[�V�������Z�b�g
    if (animNo != num)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNo = num;
        setAnim(animHandle, animNo, animTime, animTimer);
    }

    // �ړ���������Ƒ��x��ݒ�
    if (animNo == num)
    {
        angle = ROTATE_ANGLE - pGame->GetCamera()->GetHorizontalAngle();
        isMove = true;
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
        animateAndMove(ePlayer::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // �A�j���[�V�����^�C�}�[���Z�b�g
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        animateAndMove(ePlayer::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        animateAndMove(ePlayer::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        animateAndMove(ePlayer::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Space or PAD_�~ => Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_W) && rollAble)
    {
        animateAndMove(ePlayer::Roll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // �ERoll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_D) && rollAble)
    {
        animateAndMove(ePlayer::Roll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // ��Roll
    else if (Key_Roll && CheckHitKey(KEY_INPUT_A) && rollAble)
    {
        animateAndMove(ePlayer::Roll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // F => Drinking �񕜎����[�V����
    else if (CheckHitKey(KEY_INPUT_F))
    {
        // �A�j���[�V�������Z�b�g
        if (animNo != ePlayer::Drinking)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
        {
            animNo = ePlayer::Drinking;
            setAnim(animHandle, animNo, animTime, animTimer);
        }
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // G => Dying
    else if (CheckHitKey(KEY_INPUT_G))
    {
        // �A�j���[�V�������Z�b�g
        if (animNo != ePlayer::Dying)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
        {
            animNo = ePlayer::Dying;
            setAnim(animHandle, animNo, animTime, animTimer);
        }
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Idle
    else
    {
        isMove = false;
        // �A�j���[�V�������Z�b�g
        if (animNo != ePlayer::Idle)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
        {
            animNo = ePlayer::Idle;
            setAnim(animHandle, animNo, animTime, animTimer);
        }
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }

    // �ړ������ꍇ�̓����蔻��X�V�ƍ��W�Z�b�g
    if (isMove && pGame) {
        // �G�l�~�[���W�擾
        VECTOR EnemyPos = pGame->GetEnemy()->GetPos();
        // �G�l�~�[�Ƃ̓����蔻��
        pGame->GetCollision()->charaCapCol(position, moveVec, EnemyPos, CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS);
        // �ړ���̍��W�擾
        VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
        // �����蔻��X�V
        pGame->GetCollision()->clampToStageBounds(NewPos, position, rollAble);
    }

    // Todo �v���C���[�̌����ɑ΂��铮�������܂����@�ȉ��֐�����
    // ���[�_�[�̒��S�����̍��W�Ɛ��ʂ̌����ɐݒ�
    float Rad = angle * (DX_PI / 180.0f);
    float FrontVecX = -sinf(Rad);
    float FrontVecZ = -cosf(Rad);
    VECTOR FrontVector = VGet(FrontVecX, 0.0f, FrontVecZ);
    pGame->GetRadar()->addCenter(position.x, position.z, FrontVector.x, FrontVector.z);
}


/**
* @brief  �������ɂ����ʂƂ��ĕԂ�
* @return true:���� / false:���S
*/
bool Player::isAlive()
{
    if (hitPoint <= 0)
    {
        return false;
    }

#ifdef _DEBUG
    // O�ŃQ�[����ʏI��
    if (CheckHitKey(KEY_INPUT_O)) { return false; }
    // L��HP����
    if (CheckHitKey(KEY_INPUT_L)) { hitPoint -= HP_CHANGE_AMOUNT; }
#endif

    return true;

}


/**
* @brief �`�惁�\�b�h
* @note  �v���C���[��Ǐ]���邽�߃J�����p�֐��͂����ŌĂяo��
*/
void Player::draw()
{
    // ���f���Ƀ^�C�}�[�Z�b�g
    // ���ꂪ�Ȃ��ƃA�j���[�V�������Ȃ�
    MV1SetAttachAnimTime(animHandle, 0, animTimer);

    // ���f���̑傫���ύX
    MV1SetScale(animHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // ���f���̉�]
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // 3D���f���ɍ��W���Z�b�g
    MV1SetPosition(animHandle, position);

    //VECTOR rotate = MV1GetRotationXYZ(anim_handle);
    //int nRotateY = static_cast<int>(rotate.y);
    //DrawFormatString(0, 0, GetColor(0, 0, 0), "nRotateY:%d",nRotateY);

    // 3D���f���̕`��
    MV1DrawModel(animHandle);

#ifdef _DEBUG
    // �����蔻��J�v�Z���`��
    // player
    DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);
    // enemy
    VECTOR EnemyPos = pGame->GetEnemy()->GetPos();
    DrawCapsule3D(EnemyPos, VGet(EnemyPos.x, EnemyPos.y + CAP_HEIGHT, EnemyPos.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
#endif

}


/**
* @brief �v���C���[���W���擾���ĕԂ�
*/
VECTOR Player::GetPos()
{   
    return position;
}


/**
* @brief Hp���擾���ĕԂ�
*/
float Player::GetHp()
{
    return hitPoint;
}