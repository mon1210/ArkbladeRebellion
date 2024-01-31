#include "Player.h"

/**
* @brief Player�̃R���X�g���N�^
*/
Player::Player(Game *Game_)
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
    SAFE_DELETE(pOBBCol);
    SAFE_DELETE(pOBBColSword);
}


/**
* @brief ���������\�b�h
* @param[in] hit_point�@�L������HP�@�g��������̂���
*/
void Player::initialize(int hit_point)
{
    // �ϐ�������
    hitPoint = hit_point;
    currentHP = hitPoint;
    healCount = MAX_HEAL_COUNT;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    rollCoolTime = 0;
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

    // �̗p OBBCollider�C���X�^���X��   ��_���[�W���g�p
    pOBBCol = new OBBCollider(PLAYER_OBB_SCALE, PLAYER_OBB_ANGLE, PLAYER_OBB_TRANS);

    // ���p OBBCollider�C���X�^���X��   �U�����g�p
    pOBBColSword = new OBBCollider(SWORD_OBB_SCALE, SWORD_OBB_ANGLE, SWORD_OBB_TRANS);
}


/**
* @brief unordered_map���������\�b�h
* @note  �eState���Ƃ̃��\�b�h��o�^
*/
void Player::initializeStateFunctions()
{
    stateFunctionMap[PlayerState::Idle]     = [this]() { idle();    };  // �ҋ@
    stateFunctionMap[PlayerState::Move]     = [this]() { move();    };  // �ړ�
    stateFunctionMap[PlayerState::Roll]     = [this]() { roll();    };  // �O�](���)
    stateFunctionMap[PlayerState::Attack]   = [this]() { attack();  };  // �U��
    stateFunctionMap[PlayerState::Damage]   = [this]() { damage();  };  // ��_���[�W
    stateFunctionMap[PlayerState::Healing]  = [this]() { healing(); };  // ��
    stateFunctionMap[PlayerState::Death]    = [this]() { death();   };  // ���S
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
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


/**
* @brief �@�ړ��L�[�`�F�b�N
* @details ���������Ȍ���
*/
bool Player::checkMoveKey()
{
    return Key_ForwardMove || Key_BackMove || Key_Left_Move || Key_RightMove;
}


/**
* @brief �@��]�L�[�`�F�b�N
* @details ���������Ȍ���
*/
bool Player::checkRollKey()
{
    return Key_ForwardRoll || Key_LeftRoll || Key_RightRoll || Key_BackRoll && rollAble;
}


/**
* @brief ���W�Ɠ����蔻���ݒ肷�郁�\�b�h
* @note  �ړ����ɌĂяo��
*/
void Player::updateMoveAndCollision()
{
    // ���f���̍��W�E���������Ƃɒl�ݒ�
    obbAngle = VGet(0.f, angle, 0.f);
    obbTrans = VGet(position.x, position.y + PLAYER_OBB_TRANS_Y, position.z);

    // OBB�l�ύX
    pOBBCol->changeRotateMatrix(obbAngle);      // ��]
    pOBBCol->changeTranslateMatrix(obbTrans);   // �ړ�

    if (pGame)
    {
        // �G�l�~�[�Ƃ̓����蔻��
        pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS);
        // �ړ���̍��W�擾
        VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);

        // �����蔻��X�V ------
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
* @brief Attack����Idle�ɖ߂�ۂ̏������\�b�h
*/
void Player::changeAttackToIdle()
{
    // ���f����߂�
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
    // State��Idle��
    currentState = PlayerState::Idle;
    isAttackAnim = false;
}


/**
* @brief ��ԊǗ����\�b�h
* @note  ���t���[���̏���
*/
void Player::update()
{
    // ����State�ɑΉ����郁�\�b�h�Ăяo��
    stateFunctionMap[currentState]();

    // Roll��~�܂��Ă���Ƃ��̃N�[���_�E��
    if (!rollAble)
        manageRollCooldown();

    // hitPoint0�ȉ���death��
    if (hitPoint <= 0.f && !isDeath)
        currentState = PlayerState::Death;
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
        isFirst = true;
    }
    // healing��
    else if (Key_Healing && healCount > 0) {
        currentState = PlayerState::Healing;
    }
    // HP�������@Damage��    HP��0�ȉ��̍ۂɂ͒ʂ炸Death��
    if (hitPoint < currentHP && hitPoint > 0) {
        currentState = PlayerState::Damage;
    }
}


/**
* @brief Move��Ԃ̊Ǘ����\�b�h
* @note  �ړ��L�[��b����Idle
*/
void Player::move()
{
    // 
    updateMoveAndCollision();

    if (Key_ForwardMove)
    {
        // �A�j���[�V�����A�ړ�������Z�b�g
        animateAndMove(ePlayer::AnimationNum::Run, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        // �A�j���[�V�����^�C�}�[���Z�b�g
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Down => Run���[�V����(3) ���ړ�
    else if (Key_BackMove)
    {
        animateAndMove(ePlayer::AnimationNum::Run, BACKWARD_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Right => Run���[�V����(3) �E�ړ�
    else if (Key_RightMove)
    {
        animateAndMove(ePlayer::AnimationNum::Run, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    // Left => Run���[�V����(3) ���ړ�
    else if (Key_Left_Move)
    {
        animateAndMove(ePlayer::AnimationNum::Run, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Run)], &animTimer, PLAYER_ANIM_F_INCREMENT);
    }
    else
    {
        currentState = PlayerState::Idle;
    }
}


/**
* @brief Roll��Ԃ̊Ǘ����\�b�h
* @note  �A�j���[�V�����I������Idle
*/
void Player::roll()
{
    // 
    updateMoveAndCollision();

    // �ORoll
    if (Key_ForwardRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, FORWARD_ROTATION_ANGLE, 0, PLAYER_MOVE_SPEED);
        isRoll = true;
    }
    // �ERoll
    else if (Key_RightRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, RIGHT_ROTATION_ANGLE, PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }
    // ��Roll
    else if (Key_LeftRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, LEFT_ROTATION_ANGLE, -PLAYER_MOVE_SPEED, 0);
        isRoll = true;
    }
    // ��Roll
    else if (Key_BackRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::NoMoveRoll, BACK_ROTATION_ANGLE, 0, -PLAYER_MOVE_SPEED);
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
        }
    }
}


/**
* @brief Attack��Ԃ̊Ǘ����\�b�h
*/
void Player::attack()
{
    // ��i�ڂ̍U�� ===================================================================================================================
    if (isFirst)
    {
        //count += PLAYER_ANIM_F_INCREMENT;

        // �A�j���[�V�������Z�b�g
        if (!isAttackAnim)       // (int)ePlayerWS::Slash1��(int)ePlayer::Idle�������Ȃ̂ŏ�����ύX
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash1;
            setAnim(animHandle, animNum, animTimer);
            isAttackAnim = true;
        }
        // �A�j���[�V�����I����
        if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash1)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            isFirst = false;
            isAttackAnim = false;
        }
        // ��i�ڂ֍s�����ǂ���
        if (!isAttackAnim)
        {
            // B�L�[�������Ă���            count��43�b�ȏ�@�A�j���[�V����45�b��2�b�O�܂łɉ���
            if (CheckHitKey(KEY_INPUT_B)/*  && count >= 43 */)
            {
                // ��i�ڂ�
                isSecond = true;
                isAttackAnim = true;
            }
            // Idle�֖߂�
            else/* if (count >= 50 ) // �ܕb�P�\ */
            {
                changeAttackToIdle();
            }
        }

    }

    // ��i�ڂ̍U�� ===================================================================================================================
    if (isSecond)
    {
        //count += PLAYER_ANIM_F_INCREMENT

        if (animNum != (int)ePlayerWS::AnimationNum::Slash2)
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash2;
            setAnim(animHandle, animNum, animTimer);
            //count = 0;
        }
        // �A�j���[�V�����I����
        if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash2)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            isSecond = false;
            // �A�j���[�V�����I���t���O��false�Ɂ@��i�ڂɍs�����ǂ����𔻒肷��p
            isAttackAnim = false;
        }
        // �O�i�ڂɍs�����ǂ���
        if (!isAttackAnim)
        {
            // N�L�[�������Ă���        count��48�b�ȏ�@�A�j���[�V����50�b��2�b�O�܂łɉ���
            if (CheckHitKey(KEY_INPUT_N)/*  && count >= 48 */)
            {
                // �O�i�ڂ�
                isThird = true;
                isAttackAnim = true;
            }
            // Idle�֖߂�
            else
            {
                changeAttackToIdle();
            }
        }
    }

    // �O�i�ڂ̍U�� ===================================================================================================================
    if (isThird)
    {
        if (animNum != (int)ePlayerWS::AnimationNum::Slash3)
        {
            animNum = (int)ePlayerWS::AnimationNum::Slash3;
            setAnim(animHandle, animNum, animTimer);
            //count = 0;
        }
        // �A�j���[�V�����I����
        if (updateAnimation(withSwordAnimTimes[static_cast<int>(ePlayerWS::AnimationNum::Slash3)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            // Idle�֖߂�
            changeAttackToIdle();
            isThird = false;
        }
    }

    // �����蔻��(��)�ݒ� ==============================================
    // �A�j���[�V�������A�^�b�`����Ă���K�v������̂ł����ŏ���
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
    // ���f���̉E��frame�擾
    MATRIX frame_matrix = MV1GetFrameLocalWorldMatrix(animHandle, PLAYER_RIGHT_HAND_FRAME);
    // �e�̍s��ɍ��킹��
    pOBBColSword->setParentMatrix(frame_matrix);
#ifdef _DEBUG
    // �`��
    pOBBColSword->draw();
#endif

    // ����OBB,�GOBB�ł̓����蔻��
    pGame->GetCollision()->checkOBBCol(pOBBColSword, pGame->GetEnemy()->GetOBBCol());
}


/**
* @brief Damage��Ԃ̊Ǘ����\�b�h
* @norte HP�̌���
*/
void Player::damage()
{
    // ���݂�HP�X�V
    currentHP = hitPoint;
    // �A�j���[�V�������Z�b�g
    if (animNum != (int)ePlayer::AnimationNum::Damage)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = (int)ePlayer::AnimationNum::Damage;
        setAnim(animHandle, animNum, animTimer);
    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Damage)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        currentState = PlayerState::Idle;

}


/**
* @brief Healing��Ԃ̊Ǘ����\�b�h
* @note  HP�̉񕜁@�A�j���[�V�����I������Idle
*/
void Player::healing()
{
    // �A�j���[�V�������Z�b�g
    if (animNum != (int)ePlayer::AnimationNum::Drinking)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = (int)ePlayer::AnimationNum::Drinking;
        setAnim(animHandle, animNum, animTimer);
    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Drinking)], &animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        // ������HP��
        hitPoint += HEALING_VALUE;
        // �ő�ŏ�������
        hitPoint = clamp(hitPoint, 0, MAX_HP);
        // �񕜉\�񐔂����炷
        healCount--;
        // Idle��
        currentState = PlayerState::Idle;
    }
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

    // �A�j���[�V�����Đ� =======================
    animTimer += PLAYER_ANIM_F_INCREMENT;
    // ���S����animTimer�����Z�b�g���Ȃ��̂ł����ŏ���     �A�j���[�V�����I������flagON
    if (animTimer >= animTimes[static_cast<int>(ePlayer::AnimationNum::Dying)])
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
    if (hitPoint <= 0.f && isDeath)
        return false;

#ifdef _DEBUG
    // L��HP����
    if (CheckHitKey(KEY_INPUT_H)) {
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

    // 3D���f���̕`��
    MV1DrawModel(animHandle);

    // 
    MV1SetAttachAnimTime(animHandle, static_cast<int>(ePlayerWS::AnimationNum::Slash1), animTimer);
    // 55���E���Bone
    MATRIX FrameMatrix = MV1GetFrameLocalWorldMatrix(animHandle, 55);
#ifdef _DEBUG    
    VECTOR pos = VGet(0.f, 0.f, 0.f);
    pos = VTransform(pos, FrameMatrix);
    DrawSphere3D(pos, 10.f, 10, BLUE, BLUE, TRUE);

    // �����蔻��J�v�Z���`��
    //DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);

    // �`��
    pOBBCol->draw();
#endif

}


/**
* @brief Hp���擾���ĕԂ�
*/
float Player::GetHp()
{
    return hitPoint;
}


/**
* @brief healCount���擾���ĕԂ�
*/
int Player::GetHealCount()
{
    return healCount;
}


/*
* @brief pOBBCol���擾���ĕԂ�
*/
OBBCollider* Player::GetOBBCol()
{
    return pOBBCol;
}