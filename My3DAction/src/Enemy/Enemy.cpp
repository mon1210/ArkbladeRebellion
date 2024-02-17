#include <math.h>
#include "Enemy.h"

/**
* @brief Enemy�̃R���X�g���N�^
*/
Enemy::Enemy(Game *Game)
{
    pGame = Game;

    // ���f���擾
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Enemy);

}


// �f�X�g���N�^
Enemy::~Enemy()
{
    SAFE_DELETE_ARRAY(animTimes);
}


/**
* @brief ���������\�b�h
* @note  �g�������l����������HP���w��
* @param[in] hit_point  �L������HP
*/
void Enemy::initialize(float hit_point)
{
    // �ϐ�������
    hitPoint = hit_point;
    currentHP = hitPoint;
    angle = ENEMY_START_ROTATE_Y;
    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);
    moveVec = VGet(0.f, 0.f, 0.f);
    count = 0;
    toPlayerVec = VGet(0.f, 0.f, 0.f);

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, (int)eEnemy::AnimationNum::Idle);

    // unordered_map������
    initializeStateFunctions();

    // animTimes�̃T�C�Y��animationList�Ɠ����T�C�Y��
    animTimes = new float[static_cast<int>(eEnemy::AnimationNum::Dying) + 1];
    // animTimes�ɃA�j���[�V�������Ԃ�ۑ�
    for (int i = static_cast<int>(eEnemy::AnimationNum::Idle); i <= static_cast<int>(eEnemy::AnimationNum::Dying); i++)
    {
        animTimes[i] = MV1GetAnimTotalTime(animHandle, i);
    }

    // �A�j���[�V������ԏ�����
    setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);

    // �A�j���[�V�����^�C�}�[���Z�b�g
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


/**
* @brief enemyToPlayer�̍X�V�E�������Z�o�@���t���[���Ăяo��
* @note  ���t���[���̏���
*/
void Enemy::updateToPlayerVec()
{
    toPlayerVec = VSub(pGame->GetPlayer()->GetPos(), position);                         // �G�l�~�[����v���C���[�̋����x�N�g�������߂�
    vecLength = sqrtf(toPlayerVec.x * toPlayerVec.x + toPlayerVec.z * toPlayerVec.z);   // �����x�N�g���̒���
}


/**
* @brief unordered_map���������\�b�h
* @note  �eState���Ƃ̃��\�b�h��o�^
*/
void Enemy::initializeStateFunctions()
{
    stateFunctionMap[EnemyState::Wait]      = [this]() { wait();   };
    stateFunctionMap[EnemyState::Move]      = [this]() { move();   };
    stateFunctionMap[EnemyState::Chase]     = [this]() { chase();  };
    stateFunctionMap[EnemyState::Attack]    = [this]() { attack(); };
    stateFunctionMap[EnemyState::Damage]    = [this]() { damage(); };
    stateFunctionMap[EnemyState::Death]     = [this]() { death();  };

}


/**
* @brief �s����Ԃ̊Ǘ����\�b�h
* @note  ���t���[���̏���
*/
void Enemy::update()
{
    // ����State�ɑΉ����郁�\�b�h�Ăяo��
    stateFunctionMap[currentState]();

    // hitPoint0�ȉ���death��
    if (hitPoint <= 0.f && !isDeath)
        currentState = EnemyState::Death;

    // enemy��player�̋����x�N�g���̍X�V
    updateToPlayerVec();

    // Rader��Point�ɒǉ�
    pGame->GetRadar()->addPoint(position.x, position.z, eRadar::PointType::Enemy);

    // �U�����󂯂���
    if (pGame->GetPlayer()->GetIsHitFlag())
    {
        hitPoint = clampF(hitPoint, 0, ENEMY_MAX_HP); // �ő�ŏ�������
        hitPoint -= PLAYER_ATTACK;
    }
}


/**
* @brief ��ԂƃA�j���[�V������ݒ�
* @note  ��ԕύX���Ɏg�p
* @param[in] state  �ύX��̏��
* @param[in] num    �ύX��̃A�j���[�V����
*/
void Enemy::setStateAndAnim(EnemyState state, eEnemy::AnimationNum anim_num)
{
    // �J�E���g���Z�b�g
    count = 0;
    // State�ύX
    currentState = state;

    // �A�j���[�V�������Z�b�g    
    if (animNum != static_cast<int>(anim_num))   // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(anim_num);
        setAnim(animHandle, animNum, animTimer);
    }

    // ���݂̃A�j���[�V�����̍Đ����Ԃ��擾
    animTime = animTimes[static_cast<int>(anim_num)];
}


/**
* @brief �ړ���̍��W��ݒ肷��
* @note  �ړ����ɌĂяo��
*/
void Enemy::moveHandle()
{
    // ���f���̍��W�E���������Ƃɒl�ݒ�
    VECTOR ObbAngle = VGet(0.f, angle, 0.f);
    VECTOR ObbTrans = VGet(position.x, position.y + ENEMY_OBB_TRANS_Y, position.z);

    // OBB�l�ύX
    mOBBCol.changeRotateMatrix(ObbAngle);      // ��]
    mOBBCol.changeTranslateMatrix(ObbTrans);   // �ړ�

    // �ړ���܂ł̃x�N�g���擾
    VECTOR NewPos = VAdd(moveVec, position);

    // ���Ƃ̓����蔻��@�������Ă��������
    if (pGame->GetCollision()->clampToStageBounds(NewPos, position))
    {
        // ����ɓ����Ă�����ǐ�        
        if (isTargetVisible() == true)
        {
            currentState = EnemyState::Chase;
        }
    }
}


// �ȉ���ԊǗ����\�b�h ===============================================================================================
/**
* @brief Wait��Ԃ̊Ǘ����\�b�h
*/
void Enemy::wait()
{
    // �s���F�������Ȃ�
    // �U���q�b�g�t���O��܂�
    isAttackHit = false;

    // �J��
    /*
        �ړ��F
            �����F��莞�Ԃ̌o��
        �ǐՁF
            �����F����Ƀv���C���[������
        �U���F
            �����F�U���͈͓��Ƀv���C���[������
    */
    count++;

    if (count > TIME_TO_TRANSITION)   // �J�ڃ^�C�}�[�𒴂���
    {
        // ����ɓ����Ă�����ǐ�
        if (isTargetVisible() == true)
            setStateAndAnim(EnemyState::Chase, eEnemy::AnimationNum::Run);
        // Move��
        else
        {
            angle = static_cast<float>(rand() % FULL_CIRCLE_DEGREES);  // �����_���Ȋp�x���擾
            setStateAndAnim(EnemyState::Move, eEnemy::AnimationNum::Run);
        }

        // �U���t���OOFF
        isAttack = false;
    }

    // �U���͈͓��Ƀv���C���[��������
    if (pGame->GetCollision()->checkAttackArea(position, pGame->GetPlayer()->GetPos(), 250) && !isAttack)
    {
        setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
        isAttack = true;
    }

    //// HP�������@Damage��    HP��0�ȉ��̍ۂɂ͒ʂ炸Death��
    //if (hitPoint < currentHP && hitPoint > 0) {
    //    currentState = EnemyState::Damage;
    //}

    // �A�j���[�V�����^�C�}�[���Z�b�g
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


/**
* @brief Move��Ԃ̊Ǘ����\�b�h
*/
void Enemy::move()
{
    // �s���F�܂������i��(�X�e�[�W��̎�)
    // �x�N�g���Z�o
    float Rad = angle * DX_PI_F / 180.f;
    // �O�����x�N�g���̐���
    moveVec = VGet(sinf(Rad), 0.f, cosf(Rad));
    // -1����Z���邱�ƂŃx�N�g�����t�]
    moveVec = VScale(moveVec, -1.f);

    // ���W�ύX
    // �x�N�g���̑傫������Z�A�ړ����x��
    moveVec = VScale(moveVec, ENEMY_MOVE_SPEED);

    // �v���C���[�Ƃ̓����蔻��
    pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), ENEMY_CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS, CHARA_HIT_PUSH_POWER);

    // �ړ���̍��W��ݒ�
    moveHandle();

    // �J�ځF
    /*
        �ҋ@�F
            �����F��莞�Ԃ̌o��
                        �@or
                  ��莞�Ԃ̌o�߁@���@�����_���Ȑ���0
        �ǐՁF
            �����F����Ƀv���C���[������
        �U���F
            �����F�U���͈͓��Ƀv���C���[������
                        �@or
                  ��莞�Ԃ̌o�߁@���@�����_���Ȑ���1
    */
    count++;

    if (count >= TIME_TO_TRANSITION)     // �J�ڃ^�C�}�[�𒴂����̂ŏ�ԑJ��
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);

    // ����ɓ����Ă�����ǐ�
    if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // �A�j���[�V�����͂��ł�Run�Ȃ̂ŕύX�Ȃ�
    }

    // �U���͈͓��Ƀv���C���[��������
    if (pGame->GetCollision()->checkAttackArea(position, pGame->GetPlayer()->GetPos(), 250) && !isAttack)
    {
        setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
        isAttack = true;
    }

    // �A�j���[�V�����^�C�}�[���Z�b�g
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);

}


/**
* @brief Chase��Ԃ̊Ǘ����\�b�h
*/
void Enemy::chase()
{
    // �s���F������̃v���C���[��ǂ�������

    // ������0�ȉ��̎��͉������Ȃ�   // �قڒʂ�Ȃ�
    if (vecLength <= 0.f) { return; }

    // �x�N�g����P�ʃx�N�g����
    VECTOR Direction = VGet(toPlayerVec.x / vecLength, 0.f, toPlayerVec.z / vecLength);

    // �P�ʃx�N�g�����X�J���[�{�A�ړ����x��
    moveVec = VScale(Direction, ENEMY_MOVE_SPEED);
    // �t�O�p�֐����g�p�@�x�N�g������G�l�~�[�ɑ΂���v���C���[�̊p�x�����߂�
    /* �������艺�ɏ����ƁA�ڐG���Ɋp�x���ς���Ă��܂��̂Œ��Ӂ� */
    angle = atan2f(-moveVec.x, -moveVec.z) * 180.f / DX_PI_F;

    // �v���C���[�Ƃ̓����蔻��
    if (pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), ENEMY_CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS, CHARA_HIT_PUSH_POWER))
        isColHit = true;

    // �ړ���̍��W��ݒ�
    moveHandle();

    // �J��
    /*
        �ҋ@�F
            �����F�v���C���[�����삩��o��
                        �@or
                  �v���C���[�Ɠ�����
        �U���F
            �����F�U���͈͓��Ƀv���C���[������
    */
    if (isTargetVisible() == false || isColHit)
    {
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);
        isColHit = false;
    }

    // �U���͈͓��Ƀv���C���[��������
    if (pGame->GetCollision()->checkAttackArea(position, pGame->GetPlayer()->GetPos(), 250) && !isAttack)
    {
        setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
        isAttack = true;
    }

    // �A�j���[�V�����^�C�}�[���Z�b�g
    updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT);
}


/**
* @brief Attack��Ԃ̊Ǘ����\�b�h
*/
void Enemy::attack()
{
    // �s���F�U��

    // �����蔻��(��)�ݒ� 
    // �A�j���[�V�������A�^�b�`����Ă���K�v������̂ł����ŏ���
    MV1SetAttachAnimTime(animHandle, 0, animTimer);
    // ���f���̉E��frame�擾
    MATRIX frame_matrix = MV1GetFrameLocalWorldMatrix(animHandle, ENEMY_LEFT_HAND_FRAME);
    // �e�̍s��ɍ��킹��
    mOBBColHand.setParentMatrix(frame_matrix);
#ifdef _DEBUG
    // �`��
    mOBBColHand.draw();
#endif

    // ��OBB,�v���C���[OBB�ł̓����蔻��
    if (pGame->GetCollision()->checkOBBCol(mOBBColHand, pGame->GetPlayer()->GetOBBCol()))
    {
        isAttackHit = true;
    }

    // �J��
    /*
        �ҋ@�F
            �����F�A�j���[�V�����̏I��
    */
    // �A�j���[�V�����^�C�}�[���Z�b�g
    if (updateAnimation(animTime, &animTimer, ENEMY_ANIM_F_INCREMENT))
        setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);

}


/**
* @brief Damage��Ԃ̊Ǘ����\�b�h
*/
void Enemy::damage()
{
    // ���݂�HP�X�V
    currentHP = hitPoint;
    // �A�j���[�V�������Z�b�g
    setStateAndAnim(EnemyState::Damage, eEnemy::AnimationNum::Damage);
    // �A�j���[�V�����I����
    if (updateAnimation(animTimes[static_cast<int>(eEnemy::AnimationNum::Damage)], &animTimer, ENEMY_ANIM_F_INCREMENT))
        currentState = EnemyState::Wait;
}


/**
* @brief Death��Ԃ̊Ǘ����\�b�h
*/
void Enemy::death()
{
    // �A�j���[�V�������Z�b�g
    setStateAndAnim(EnemyState::Death, eEnemy::AnimationNum::Dying);
    // �A�j���[�V�����Đ� =======================
    animTimer += ENEMY_ANIM_F_INCREMENT;
    // ���S����animTimer�����Z�b�g���Ȃ��̂ł����ŏ���     �A�j���[�V�����I������flagON
    if (animTimer >= animTimes[static_cast<int>(eEnemy::AnimationNum::Dying)])
        isDeath = true;
}
// �ȏ��ԊǗ����\�b�h ===============================================================================================


/**
* @brief   �G�l�~�[�̎��상�\�b�h
* @return  true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������
*/
bool Enemy::isTargetVisible()
{
    /*
        �EEnemy�̍��W(x,z)���~�̒��S�Ƃ��čl����
        �EPlayer�̍��W��_�Ƃ��čl����
        �E�~�̔��a��10

        �_�Ɖ~�̓����蔻����g���A�_���~�̒��ɂ�������true
    */
    // �~�̔��a���x�N�g�����Z���Ȃ�����true��Ԃ�
    if (vecLength <= ENEMY_VIEW_RADIUS)
    {
        return true;
    }

    return false;
}


/**
* @brief  �������ɂ����ʂƂ��ĕԂ�
* @return true:���� / false:���S
*/
bool Enemy::isAlive()
{
    // hitPoint��0�ȉ�
    if (hitPoint <= 0.f && isDeath)
        return false;

#ifdef _DEBUG
    // L��HP����
    if (CheckHitKey(KEY_INPUT_U)) {
        hitPoint = clampF(hitPoint, 0, ENEMY_MAX_HP); // �ő�ŏ�������
        hitPoint -= HP_CHANGE_AMOUNT;
    }
#endif

    return true;
}


/**
* @brief �`�惁�\�b�h
*/
void Enemy::draw()
{
    // ���f���Ƀ^�C�}�[�Z�b�g
    // ���ꂪ�Ȃ��ƃA�j���[�V�������Ȃ�
    MV1SetAttachAnimTime(animHandle, 0, animTimer);

    // ��ʂɉf��ʒu��3D���f�����ړ�
    MV1SetPosition(animHandle, position);

    // ���f���̑傫���ύX
    MV1SetScale(animHandle, VGet(ENEMY_MODEL_SCALE, ENEMY_MODEL_SCALE, ENEMY_MODEL_SCALE));

    // ���f���̉�]
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // �R�c���f���̕`��
    MV1DrawModel(animHandle);

#ifdef _DEBUG
    // �����蔻��J�v�Z���`��
    //DrawCapsule3D(position, VGet(position.x, position.y + ENEMY_CAP_HEIGHT, position.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);

    // �`��
    mOBBCol.draw();
#endif
}


/*
* @brief mOBBCol���擾���ĕԂ�
*/
OBBCollider Enemy::GetOBBCol()
{
    return mOBBCol;
}