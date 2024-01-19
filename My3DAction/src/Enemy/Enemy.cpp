#include <math.h>
#include "Enemy.h"

/**
* @brief Enemy�̃R���X�g���N�^
*/
Enemy::Enemy(Game *Game_)
{
    pGame = Game_;

    // ���f���擾
    if (pGame)
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Enemy);

}


// �f�X�g���N�^
Enemy::~Enemy()
{
    delete[] animTimes;
}


/**
* @brief ���������\�b�h
* @note
*/
void Enemy::initialize(int hit_point)
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

    // enemy��player�̋����x�N�g���̍X�V
    updateToPlayerVec();

    // Rader��Point�ɒǉ�
    pGame->GetRadar()->addPoint(position.x, position.z, eRadar::PointType::Enemy);
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


// �ȉ���ԊǗ����\�b�h ===============================================================================================
/**
* @brief Wait��Ԃ̊Ǘ����\�b�h
*/
void Enemy::wait()
{
    // �s���F�������Ȃ�

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
            angle = (rand() % FULL_CIRCLE_DEGREES);  // �����_���Ȋp�x���擾
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

    // HP�������@Damage��    HP��0�ȉ��̍ۂɂ͒ʂ炸Death��
    if (hitPoint < currentHP && hitPoint > 0) {
        currentState = EnemyState::Damage;
    }

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
    pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS);

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
    {
        // 0 or 1 �����_���ȕϐ��擾
        int RandomStateIndex = rand() % 2;
        switch (RandomStateIndex)
        {
            case 0: // Idle��
                setStateAndAnim(EnemyState::Wait, eEnemy::AnimationNum::Idle);
                break;
            case 1: // Attack��
                setStateAndAnim(EnemyState::Attack, eEnemy::AnimationNum::Swiping);
                isAttack = true;
                break;
        }
    }
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
    if (pGame->GetCollision()->charaCapCol(position, moveVec, pGame->GetPlayer()->GetPos(), CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS))
        isColHit = true;

    // �ړ���܂ł̃x�N�g���擾
    VECTOR NewPos = VAdd(moveVec, position);

    // ���Ƃ̓����蔻��
    pGame->GetCollision()->clampToStageBounds(NewPos, position);

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
    DrawString(0, 0, "Attack", RED);// Debug

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
            currentState = EnemyState::Death;
        }
    }
#ifdef _DEBUG
    // L��HP����
    if (CheckHitKey(KEY_INPUT_U)) {
        hitPoint = clamp(hitPoint, 0, MAX_HP); // �ő�ŏ�������
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
    MV1SetScale(animHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

    // ���f���̉�]
    MV1SetRotationXYZ(animHandle, VGet(0.f, angle * DX_PI_F / 180.f, 0.f));

    // �R�c���f���̕`��
    MV1DrawModel(animHandle);

#ifdef _DEBUG
    // �����蔻��J�v�Z���`��
    DrawCapsule3D(position, VGet(position.x, position.y + CAP_HEIGHT, position.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
#endif
}
