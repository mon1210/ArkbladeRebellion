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
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);

    angle = PLAYER_START_ROTATE_Y;

    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, (int)ePlayer::AnimationNum::Idle);

    // unordered_map������
    initializeStateFunctions();
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
    if (animNum != static_cast<int>(num))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(num);
        setAnim(animHandle, animNum, animTime, animTimer);
    }

    // �ړ���������Ƒ��x��ݒ�
    if (animNum == static_cast<int>(num))
    {
        angle = ROTATE_ANGLE - pGame->GetCamera()->GetHorizontalAngle();
        isMove = true;
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


/**
* @brief �ړ��L�[�`�F�b�N
* @note  ���������Ȍ���
*/
bool Player::checkMoveKey()
{
    return Key_ForwardMove || Key_BackMove || Key_Left_Move || Key_RightMove;
}


/**
* @brief �O�]�L�[�`�F�b�N
* @note  ���������Ȍ���
*/
bool Player::checkRollKey()
{
    return Key_ForwardRoll || Key_LeftRoll || Key_RightRoll && rollAble;
}


/**
* @brief unordered_map���������\�b�h
* @note  �eState���Ƃ̃��\�b�h��o�^
*/
void Player::initializeStateFunctions()
{
    stateFunctionMap[PlayerState::Idle]     = [this]() { Idle();    };  // �ҋ@
    stateFunctionMap[PlayerState::Move]     = [this]() { Move();    };  // �ړ�
    stateFunctionMap[PlayerState::Roll]     = [this]() { Roll();    };  // �O�](���)
    stateFunctionMap[PlayerState::Attack]   = [this]() { Attack();  };  // �U��
    stateFunctionMap[PlayerState::Damage]   = [this]() { Damage();  };  // ��_���[�W
    stateFunctionMap[PlayerState::Healing]  = [this]() { Healing(); };  // ��
    stateFunctionMap[PlayerState::Death]    = [this]() { Death();   };  // ���S
}


/**
* @brief ��ԊǗ����\�b�h
* @note  ���t���[���̏���
*/
void Player::update()
{
    // ����State�ɑΉ����郁�\�b�h�Ăяo��
    stateFunctionMap[currentState]();

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
* @brief Idle��Ԃ̊Ǘ����\�b�h
*/
void Player::Idle()
{
    isMove = false;
    // �ړ��x�N�g����������
    moveVec = VGet(0.f, 0.f, 0.f);

    // �A�j���[�V�������Z�b�g
    if (animNum != (int)ePlayer::AnimationNum::Idle)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = (int)ePlayer::AnimationNum::Idle;
        setAnim(animHandle, animNum, animTime, animTimer);
    }
    if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
        animTimer = 0.f;

    if (checkMoveKey()) {
        currentState = PlayerState::Move;
    }
    else if (checkRollKey()) {
        currentState = PlayerState::Roll;
    }
    else if (CheckHitKey(KEY_INPUT_F)) {
        currentState = PlayerState::Healing;
    }
    else if (CheckHitKey(KEY_INPUT_G)) {
        currentState = PlayerState::Death;
    }
}


/**
* @brief Move��Ԃ̊Ǘ����\�b�h
* @note  �ړ��L�[��b����Idle
*/
void Player::Move()
{
    if (Key_ForwardMove || PadInput & PAD_INPUT_UP)
    {
        // �A�j���[�V�����A�ړ�������Z�b�g
        animateAndMove(ePlayer::AnimationNum::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // �A�j���[�V�����^�C�}�[���Z�b�g
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        animateAndMove(ePlayer::AnimationNum::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
            animTimer = 0.f;
    }
    else
    {
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Roll��Ԃ̊Ǘ����\�b�h
* @note  �A�j���[�V�����I������Idle    Todo �A��Roll
*/
void Player::Roll()
{
    // Space or PAD_�~ => Roll
    if (Key_ForwardRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
    }
    // �ERoll
    else if (Key_RightRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
    }
    // ��Roll
    else if (Key_LeftRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
    }

    // �A�j���[�V�����I����
    if (rollAble)
    {
        if (updateAnimation(animTime, animTimer, PLAYER_ROLL_ANIM_F_INCREMENT))
        {
            animTimer = 0.f;
            rollAble = false;
            currentState = PlayerState::Idle;
        }
    }
}


/**
* @brief Attack��Ԃ̊Ǘ����\�b�h
*/
void Player::Attack()
{

}


/**
* @brief Damage��Ԃ̊Ǘ����\�b�h
* @norte HP�̌����@HP <= 0��Death��
*/
void Player::Damage()
{
    if (hitPoint <= 0) {
        currentState = PlayerState::Death;
    }

}


/**
* @brief Healing��Ԃ̊Ǘ����\�b�h
* @note  HP�̉񕜁@�A�j���[�V�����I������Idle
*/
void Player::Healing()
{
    // F => Drinking �񕜎����[�V����
    if (CheckHitKey(KEY_INPUT_F))
    {
        // �A�j���[�V�������Z�b�g
        if (animNum != (int)ePlayer::AnimationNum::Drinking)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
        {
            animNum = (int)ePlayer::AnimationNum::Drinking;
            setAnim(animHandle, animNum, animTime, animTimer);
        }

    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        animTimer = 0.f;
        // ������HP��
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Death��Ԃ̊Ǘ����\�b�h
* @note  HP��0�ł����@�A�j���[�V�����I�����AisAlive��false�ɂ��ăQ�[���I�� 
*/
void Player::Death()
{
    // G => Dying
    if (CheckHitKey(KEY_INPUT_G))
    {
        // �A�j���[�V�������Z�b�g
        if (animNum != (int)ePlayer::AnimationNum::Dying)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
        {
            animNum = (int)ePlayer::AnimationNum::Dying;
            setAnim(animHandle, animNum, animTime, animTimer);
        }

    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTime, animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        animTimer = 0.f;
    }
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