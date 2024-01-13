#include "Player.h"

/**
* @brief Player�̃R���X�g���N�^
*/
Player::Player(Game* Game_)
{
    pGame = Game_;

    // ���f���擾
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
}


/**
* @brief �f�X�g���N�^
* @note  �|�C���^pGame��Delete��Game�N���X�ł��Ă���̂ŁA�L�q�̕K�v�Ȃ�
*/
Player::~Player()
{
    delete[] animTimes;
    delete[] withSwordAnimTimes;
}


/**
* @brief ���������\�b�h
* @note
*/
void Player::initialize(int hit_point)
{
    // �ϐ�������
    hitPoint = hit_point;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    rollCoolTime = 0;
    isMove = false;
    rollAble = true;

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, (int)ePlayer::AnimationNum::Idle);

    // unordered_map������
    initializeStateFunctions();

    // animTimes�̃T�C�Y���w��@�A�j���[�V�����ԍ��Ō�� + 1
    animTimes = new float[static_cast<int>(ePlayer::AnimationNum::Dying) + 1];
    // �A�j���[�V�������Ԃ��擾
    for (int i = static_cast<int>(ePlayer::AnimationNum::Idle); i <= static_cast<int>(ePlayer::AnimationNum::Dying); i++)
    {
        animTimes[i] = MV1GetAnimTotalTime(animHandle, i);
    }

    // ����������������f���̃A�j���[�V�������Ԃ��擾
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::PlayerWithSword);
    withSwordAnimTimes = new float[static_cast<int>(ePlayerWS::AnimationNum::Slash3) + 1];
    for (int i = static_cast<int>(ePlayerWS::AnimationNum::Idle); i <= static_cast<int>(ePlayerWS::AnimationNum::Slash3); i++)
    {
        withSwordAnimTimes[i] = MV1GetAnimTotalTime(animHandle, i);
    }

    // ���f����߂�
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
}


/**
* @brief unordered_map���������\�b�h
* @note  �eState���Ƃ̃��\�b�h��o�^
*/
void Player::initializeStateFunctions()
{
    stateFunctionMap[PlayerState::Idle] = [this]() { idle();    };  // �ҋ@
    stateFunctionMap[PlayerState::Move] = [this]() { move();    };  // �ړ�
    stateFunctionMap[PlayerState::Roll] = [this]() { roll();    };  // �O�](���)
    stateFunctionMap[PlayerState::Attack] = [this]() { attack();  };  // �U��
    stateFunctionMap[PlayerState::Damage] = [this]() { damage();  };  // ��_���[�W
    stateFunctionMap[PlayerState::Healing] = [this]() { healing(); };  // ��
    stateFunctionMap[PlayerState::Death] = [this]() { death();   };  // ���S
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
void Player::animateAndMove(ePlayer::AnimationNum num, float ROTATE_ANGLE, float move_x, float move_z)
{
    // �A�j���[�V�������Z�b�g
    if (animNum != static_cast<int>(num))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(num);
        setAnim(animHandle, animNum, animTimer);
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
* @brief Roll�̃N�[���_�E���Ǘ����\�b�h
* @note  �N�[���^�C�������炵�A0�ɂȂ��Roll���ł���悤��
*/
void Player::manageRollCooldown()
{            
    // �N�[���^�C�������炷
    rollCoolTime -= PLAYER_ANIM_F_INCREMENT;

    // �N�[���^�C����0�ȉ�
    if (rollCoolTime <= 0)
    {
        // �N�[���^�C����default��
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::NoMoveRoll)];

        rollAble = true;
    }
}


/**
* @brief ��ԊǗ����\�b�h
* @note  ���t���[���̏���
*/
void Player::update()
{
    // ����State�ɑΉ����郁�\�b�h�Ăяo��
    stateFunctionMap[currentState]();

    // �ȉ��ړ������� -------------------------------------------------------------------------------------------------
    if (isMove && pGame) {
        // �G�l�~�[�Ƃ̓����蔻��
        pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS);
        // �ړ���̍��W�擾
        VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);

        // �����蔻��X�V
        // roll�ȊO�̂Ƃ�(Roll�̃N�[���^�C����default�l�̎�)
        if (rollCoolTime == 0)
            rollAble = pGame->GetCollision()->clampToStageBounds(NewPos, position);
        // roll���̎�
        else
        {
            // �����蔻��X�V
            pGame->GetCollision()->clampToStageBounds(NewPos, position);
            // Roll�̃N�[���_�E��
            manageRollCooldown();
        }
    }
    // �ȏ�ړ������� -------------------------------------------------------------------------------------------------

    // Roll��~�܂��Ă���Ƃ��̃N�[���_�E��
    if (!rollAble)
        manageRollCooldown();

    // Todo �v���C���[�̌����ɑ΂��铮�������܂����@�ȉ��֐�����
    // ���[�_�[�̒��S�����̍��W�Ɛ��ʂ̌����ɐݒ�
    float Rad = angle * (DX_PI / 180.0f);
    float FrontVecX = -sinf(Rad);
    float FrontVecZ = -cosf(Rad);
    VECTOR FrontVector = VGet(FrontVecX, 0.0f, FrontVecZ);
    pGame->GetRadar()->addCenter(position.x, position.z, FrontVector.x, FrontVector.z);
}


// �ȉ���ԊǗ����\�b�h ===============================================================================================
/**
* @brief Idle��Ԃ̊Ǘ����\�b�h
*/
void Player::idle()
{
    // �ړ��x�N�g����������
    moveVec = VGet(0.f, 0.f, 0.f);

    // �A�j���[�V�������Z�b�g
    if (animNum != (int)ePlayer::AnimationNum::Idle)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = (int)ePlayer::AnimationNum::Idle;
        setAnim(animHandle, animNum, animTimer);
    }
    updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Idle)], &animTimer, PLAYER_ANIM_F_INCREMENT);

    // �J�� ------------------------------------------------------------------------------------------
    if (checkMoveKey()) {
        currentState = PlayerState::Move;
    }
    else if (checkRollKey() && rollAble) {
        currentState = PlayerState::Roll;
        /*
            ���[�����O�̃N�[���^�C����ǉ�
            roll_coolTime = Const.MAX_ROLLING_COOLTIME + animTime;
        */
        // animTime��Roll�̐��ɂ���悤�ɁA�z����쐬���Ď擾
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::NoMoveRoll)];

    }
    // attack��
    else if (Key_Attack) {
        currentState = PlayerState::Attack;
        // ��������������f���ɕύX
        if (pGame)
            animHandle = pGame->GetModelManager()->GetHandle(ModelType::PlayerWithSword);
    }
    // healing��
    else if (Key_Healing) {
        currentState = PlayerState::Healing;
    }
}


/**
* @brief Move��Ԃ̊Ǘ����\�b�h
* @note  �ړ��L�[��b����Idle
*/
void Player::move()
{
    if (Key_ForwardMove || PadInput & PAD_INPUT_UP)
    {
        // �A�j���[�V�����A�ړ�������Z�b�g
        animateAndMove(ePlayer::AnimationNum::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // �A�j���[�V�����^�C�}�[���Z�b�g
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (Key_BackMove || PadInput & PAD_INPUT_DOWN)
    {
        animateAndMove(ePlayer::AnimationNum::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (Key_RightMove || PadInput & PAD_INPUT_RIGHT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (Key_Left_Move || PadInput & PAD_INPUT_LEFT)
    {
        animateAndMove(ePlayer::AnimationNum::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    else
    {
        currentState = PlayerState::Idle;
        isMove = false;
    }
}


/**
* @brief Roll��Ԃ̊Ǘ����\�b�h
* @note  �A�j���[�V�����I������Idle
*/
void Player::roll()
{
    // Space or PAD_�~ => Roll
    if (Key_ForwardRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        isRoll = true;
    }
    // �ERoll
    if (Key_RightRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }
    // ��Roll
    if (Key_LeftRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }

    // �A�j���[�V�����I����
    if (rollAble)
    {
        if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::NoMoveRoll)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            currentState = PlayerState::Idle;
            rollAble = false;	
            isRoll = false;
            isMove = false;
        }
    }
}


/**
* @brief Attack��Ԃ̊Ǘ����\�b�h
*/
void Player::attack()
{
    if (Key_Attack)
    {
        // �A�j���[�V�������Z�b�g
        if (!isAttackAnim)       // (int)ePlayerWS::Slash1��(int)ePlayer::Idle�������Ȃ̂ŏ�����ύX
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash1;
            setAnim(animHandle, animNum, animTimer);
            isAttackAnim = true;
        }
    }

    if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash1)], &animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        // ���f����߂�
        if (pGame)
            animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
        currentState = PlayerState::Idle;
        isAttackAnim = false;
    }

}


/**
* @brief Damage��Ԃ̊Ǘ����\�b�h
* @norte HP�̌���
*/
void Player::damage()
{
}


/**
* @brief Healing��Ԃ̊Ǘ����\�b�h
* @note  HP�̉񕜁@�A�j���[�V�����I������Idle
*/
void Player::healing()
{
    // F => Drinking �񕜎����[�V����
    if (Key_Healing)
    {
        // �A�j���[�V�������Z�b�g
        if (animNum != (int)ePlayer::AnimationNum::Drinking)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
        {
            animNum = (int)ePlayer::AnimationNum::Drinking;
            setAnim(animHandle, animNum, animTimer);
        }

    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Drinking)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        // ������HP��
        currentState = PlayerState::Idle;
}


/**
* @brief Death��Ԃ̊Ǘ����\�b�h
* @note  HP��0�ł����@�A�j���[�V�����I�����A�Q�[���I��
*/
void Player::death()
{
    // �A�j���[�V�������Z�b�g
    if (animNum != (int)ePlayer::AnimationNum::Dying)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = (int)ePlayer::AnimationNum::Dying;
        setAnim(animHandle, animNum, animTimer);
    }

    // �A�j���[�V�����I����A���S�t���O��true��
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Dying)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        isDeath = true;
}
// �ȏ��ԊǗ����\�b�h ===============================================================================================


/**
* @brief  �������ɂ����ʂƂ��ĕԂ�
* @return true:���� / false:���S
*/
bool Player::isAlive()
{
    // hitPoint��0�ȉ�
    if (hitPoint <= 0.f)
    {
        if (isDeath)
        {
            return false;
        }
        // ��ɓ���
        else
        {
            // ���S��Ԃ�
            currentState = PlayerState::Death;
        }
    }

#ifdef _DEBUG
    // L��HP����
    if (CheckHitKey(KEY_INPUT_L)) {
        hitPoint = clamp(hitPoint, 0, MAX_HP); // �ő�ŏ�������
        hitPoint -= HP_CHANGE_AMOUNT;
    }
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

    // 
    MV1SetAttachAnimTime(animHandle, static_cast<int>(ePlayer::AnimationNum::Slash1), animTimer);
    // 41���E���Bone
    MATRIX FrameMatrix = MV1GetFrameLocalWorldMatrix(animHandle, 41);
#ifdef _DEBUG    
    VECTOR pos = VGet(0.f, 0.f, 0.f);
    pos = VTransform(pos, FrameMatrix);
    DrawSphere3D(pos, 10.f, 10, BLUE, BLUE, TRUE);

    // �����蔻��J�v�Z���`��
    DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);
#endif

}


/**
* @brief Hp���擾���ĕԂ�
*/
float Player::GetHp()
{
    return hitPoint;
}

