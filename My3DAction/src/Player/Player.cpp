#include "Player.h"


// �R���X�g���N�^
Player::Player(Game *Game)
{
    pGame = Game;

    // ���f���擾
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
}


/*
    �f�X�g���N�^
    �|�C���^pGame��Delete��Game�N���X�ł��Ă���̂ŁA�L�q�̕K�v�Ȃ�
*/
Player::~Player()
{
    SAFE_DELETE_ARRAY(animTimes);
    SAFE_DELETE_ARRAY(withSwordAnimTimes);
}


// ���������\�b�h
void Player::initialize(int hit_point)
{
    // �ϐ�������
    hitPoint = hit_point;
    currentHP = hitPoint;
    healCount = MAX_HEAL_COUNT;
    angle = PLAYER_START_ROTATE_Y;
    position = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y, PLAYER_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    rollCoolTime = 0.f;
    rollAble = true;
    isAttackHit = false;

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, static_cast<int>(ePlayer::AnimationNum::Idle));

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
    mOBBCol = OBBCollider(PLAYER_OBB_SCALE, PLAYER_OBB_ANGLE, PLAYER_OBB_TRANS);

    // ���p OBBCollider�C���X�^���X��   �U�����g�p
    mOBBColSword = OBBCollider(SWORD_OBB_SCALE, SWORD_OBB_ANGLE, SWORD_OBB_TRANS);
}


// unordered_map���������\�b�h
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


// �ړ����̍s���Ǘ�
void Player::animateAndMove(ePlayer::AnimationNum num, float rotate_angle, float move_x, float move_z)
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
        angle = rotate_angle - pGame->GetCamera()->GetHorizontalAngle();
        moveVec.x = move_x;
        moveVec.z = move_z;
    }
}


// �ړ��L�[�`�F�b�N
bool Player::checkMoveKey()
{
    return Key_ForwardMove || Key_BackMove || Key_Left_Move || Key_RightMove;
}


// ��]�L�[�`�F�b�N
bool Player::checkRollKey()
{
    return Key_ForwardRoll || Key_LeftRoll || Key_RightRoll || Key_BackRoll && rollAble;
}


// �ړ���̍��W��ݒ肷��
void Player::moveHandle()
{
    // ���f���̍��W�E���������Ƃɒl�ݒ�
    VECTOR ObbAngle = VGet(0.f, angle, 0.f);
    VECTOR ObbTrans = VGet(position.x, position.y + PLAYER_OBB_TRANS_Y, position.z);

    // OBB�l�ύX
    mOBBCol.changeRotateMatrix(ObbAngle);      // ��]
    mOBBCol.changeTranslateMatrix(ObbTrans);   // �ړ�

    if (pGame)
    {
        // �����蔻��X�V ------
        // roll�ȊO�̂Ƃ�(�Q�[���J�n��)
        if (!isRoll)
        {            
            // �G�l�~�[�Ƃ̓����蔻��
            pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, ENEMY_CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS, CHARA_HIT_PUSH_POWER);
            // �ړ���̍��W�擾
            VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
            // �n�ʂƂ̔��肪����Ƃ���Roll�\
            rollAble = pGame->GetCollision()->clampToStageBounds(NewPos, position);
        }
        // roll���̎�
        else
        {
            // �G�l�~�[�Ƃ̓����蔻��
            pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetEnemy()->GetPos(), CAP_HEIGHT, ENEMY_CAP_HEIGHT, PLAYER_CAP_RADIUS, ENEMY_CAP_RADIUS, 0.f);
            // �ړ���̍��W�擾
            VECTOR NewPos = pGame->GetCamera()->moveAlongHAngle(moveVec, position);
            // �����蔻��X�V
            pGame->GetCollision()->clampToStageBounds(NewPos, position);
            // Roll�̃N�[���_�E��
            manageRollCooldown();
        }
    }

}


// Roll�̃N�[���_�E���Ǘ����\�b�h
void Player::manageRollCooldown()
{
    // �N�[���^�C�������炷
    rollCoolTime -= PLAYER_ANIM_F_INCREMENT;

    // �N�[���^�C����0�ȉ�
    if (rollCoolTime <= 0)
    {
        // �N�[���^�C����default��
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::Roll)];

        rollAble = true;
    }
}


// Attack����Idle�ɖ߂�ۂ̏������\�b�h
void Player::changeAttackToIdle()
{
    // ���f����߂�
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Player);
    // State��Idle��
    currentState = PlayerState::Idle;
    isAttackAnim = false;
}


// ��ԊǗ����\�b�h
void Player::update()
{
    // ����State�ɑΉ����郁�\�b�h�Ăяo��
    stateFunctionMap[currentState]();

    // Roll��~�܂��Ă���Ƃ��̃N�[���_�E��
    if (!rollAble)
        manageRollCooldown();

    // �U�����󂯂���      Roll���͖��G
    if (pGame->GetEnemy()->GetIsHitFlag() && !isRoll)
    {
        hitPoint = clamp(hitPoint -= ENEMY_ATTACK, 0, MAX_HP); // �ő�ŏ�������
    }

    // hitPoint0�ȉ���death��
    if (hitPoint <= 0 && !isDeath)
        currentState = PlayerState::Death;
}


// �ȉ���ԊǗ����\�b�h ===============================================================================================
// Idle��Ԃ̊Ǘ�
void Player::idle()
{
    // �ړ��x�N�g����������
    moveVec = VGet(0.f, 0.f, 0.f);
    // �U���q�b�g�t���O��܂�
    isAttackHit = false;

    // �A�j���[�V�������Z�b�g
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Idle))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Idle);
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
        rollCoolTime = MAX_ROLL_COOL_TIME + animTimes[static_cast<int>(ePlayer::AnimationNum::Roll)];

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


// Move��Ԃ̊Ǘ�
void Player::move()
{
    // �ړ���̍��W��ݒ�
    moveHandle();

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


// Roll��Ԃ̊Ǘ�
void Player::roll()
{
    // �ړ���̍��W��ݒ�
    moveHandle();

    // �ORoll
    if (Key_ForwardRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, FORWARD_ROTATION_ANGLE, 0, PLAYER_ROLL_SPEED);
        isRoll = true;
    }
    // �ERoll
    else if (Key_RightRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, RIGHT_ROTATION_ANGLE, PLAYER_ROLL_SPEED, 0);
        isRoll = true;
    }
    // ��Roll
    else if (Key_LeftRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, LEFT_ROTATION_ANGLE, -PLAYER_ROLL_SPEED, 0);
        isRoll = true;
    }
    // ��Roll
    else if (Key_BackRoll && !isRoll)
    {
        animateAndMove(ePlayer::AnimationNum::Roll, BACK_ROTATION_ANGLE, 0, -PLAYER_ROLL_SPEED);
        isRoll = true;
    }

    // �A�j���[�V�����I����
    if (rollAble)
    {
        if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Roll)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        {
            currentState = PlayerState::Idle;
            rollAble = false;
            isRoll = false;
        }
    }
}


// Attack��Ԃ̊Ǘ�
void Player::attack()
{
    // ��i�ڂ̍U�� ===================================================================================================================
    if (isFirst)
    {
        //count += PLAYER_ANIM_F_INCREMENT;

        // �A�j���[�V�������Z�b�g
        if (!isAttackAnim)  // static_cast<int>(ePlayerWS::Slash1)��static_cast<int>(ePlayer::Idle)�������Ȃ̂ŏ�����ύX
        {
            animNum = static_cast<int>(ePlayerWS::AnimationNum::Slash1);
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
    else if (isSecond)
    {
        //count += PLAYER_ANIM_F_INCREMENT

        if (animNum != static_cast<int>(ePlayerWS::AnimationNum::Slash2))
        {
            animNum = static_cast<int>(ePlayerWS::AnimationNum::Slash2);
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
    else if (isThird)
    {
        if (animNum != static_cast<int>(ePlayerWS::AnimationNum::Slash3))
        {
            animNum = static_cast<int>(ePlayerWS::AnimationNum::Slash3);
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
    mOBBColSword.setParentMatrix(frame_matrix);

    // ��OBB�`��
    if (CheckHitKey(KEY_INPUT_E))
        mOBBColSword.draw(WHITE);

    // ����OBB,�GOBB�ł̓����蔻��
    if (pGame->GetCollision()->checkOBBCol(mOBBColSword, pGame->GetEnemy()->GetOBBCol()))
    {
        isAttackHit = true;
    }
}


// Damage��Ԃ̊Ǘ�
void Player::damage()
{
    // ���݂�HP�X�V
    currentHP = hitPoint;
    // �A�j���[�V�������Z�b�g
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Damage))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Damage);
        setAnim(animHandle, animNum, animTimer);
    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Damage)], &animTimer, PLAYER_ANIM_F_INCREMENT))
        currentState = PlayerState::Idle;

}


// Healing��Ԃ̊Ǘ�
void Player::healing()
{
    // �A�j���[�V�������Z�b�g
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Drinking))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Drinking);
        setAnim(animHandle, animNum, animTimer);
    }

    // �A�j���[�V�����I����
    if (updateAnimation(animTimes[static_cast<int>(ePlayer::AnimationNum::Drinking)], &animTimer, PLAYER_ANIM_F_INCREMENT))
    {
        // HP�� �ő�ŏ�������
        hitPoint = clamp(hitPoint += HEALING_VALUE, 0, MAX_HP);
        // �񕜉\�񐔂����炷
        healCount--;
        // Idle��
        currentState = PlayerState::Idle;
    }
}


/*
    Death��Ԃ̊Ǘ�
    HP��0�ł����ɓ���
    �A�j���[�V�����I�����A�Q�[���I��
*/
void Player::death()
{
    // �A�j���[�V�������Z�b�g
    if (animNum != static_cast<int>(ePlayer::AnimationNum::Dying))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(ePlayer::AnimationNum::Dying);
        setAnim(animHandle, animNum, animTimer);
    }

    // �A�j���[�V�����Đ� =======================
    animTimer += PLAYER_ANIM_F_INCREMENT;
    // ���S����animTimer�����Z�b�g���Ȃ��̂ł����ŏ���     �A�j���[�V�����I������flagON
    if (animTimer >= animTimes[static_cast<int>(ePlayer::AnimationNum::Dying)])
        isDeath = true;
}
// �ȏ��ԊǗ����\�b�h ===============================================================================================


// �������ɂ����ʂƂ��ĕԂ�
bool Player::isAlive()
{
    // hitPoint��0�ȉ�
    if (hitPoint <= 0 && isDeath)
        return false;

    return true;
}


// �`�惁�\�b�h
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

    // �����蔻��J�v�Z���`��
    if (CheckHitKey(KEY_INPUT_Q))
        DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);

    // OBB�`��
    if (CheckHitKey(KEY_INPUT_E))
    {
        // �������Ă���Ƃ��͐ԐF��
        if (pGame->GetEnemy()->GetIsHitFlag())
            mOBBCol.draw(RED);
        else
            mOBBCol.draw(WHITE);
    }

}


// healCount���擾���ĕԂ�
int Player::GetHealCount()
{
    return healCount;
}


// mOBBCol���擾���ĕԂ� 
OBBCollider Player::GetOBBCol()
{
    return mOBBCol;
}