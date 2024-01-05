#include <math.h>
#include "Enemy.h"

/**
* @brief Enemy�̃R���X�g���N�^
*/
Enemy::Enemy(Game *Game_)
{
    pGame = Game_;

    // ���f���擾
    if (pGame) {
        animHandle = pGame->GetModelManager()->GetHandle(ModelType::Enemy);
        tileHandle = pGame->GetBG()->GetModelHandle();
    }

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
    setAnimationHandle(eEnemy::AnimationNum::Idle);
    animTime = animTimes[static_cast<int>(eEnemy::AnimationNum::Idle)];
}


/**
* @brief �A�j���[�V������ݒ肷��
* @param[in] num    �A�j���[�V�����ԍ�
*/
void Enemy::setAnimationHandle(eEnemy::AnimationNum num) {
    // �A�j���[�V�������Z�b�g
    if (animNum != static_cast<int>(num))  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNum = static_cast<int>(num);
        setAnim(animHandle, animNum, animTimer);
    }
};


/**
* @brief enemyToPlayer�̍X�V�E�������Z�o�@���t���[���Ăяo��
* @note  ���t���[���̏���
*/
void Enemy::updateToPlayerVec() 
{
    toPlayerVec = VSub(pGame->GetPlayer()->GetPos(), position);   // �G�l�~�[����v���C���[�̋����x�N�g�������߂�
    vecLength = sqrtf(toPlayerVec.x * toPlayerVec.x + toPlayerVec.z * toPlayerVec.z); // �����x�N�g���̒���
}


/**
* @brief unordered_map���������\�b�h
* @note  �eState���Ƃ̃��\�b�h��o�^
*/
void Enemy::initializeStateFunctions()
{
    stateFunctionMap[EnemyState::Wait]  = [this]() { wait();  };
    stateFunctionMap[EnemyState::Move]  = [this]() { move();  };
    stateFunctionMap[EnemyState::Chase] = [this]() { chase(); };
    //stateFunctionMap[EnemyState::Attack] = [this]() { attack();  };
    //stateFunctionMap[EnemyState::Damage] = [this]() { damage();  };  
    //stateFunctionMap[EnemyState::Death] = [this]() { death();   };

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

    // �A�j���[�V�����^�C�}�[���Z�b�g
    updateAnimation(animTime, &animTimer, PLAYER_ANIM_F_INCREMENT);

}


/**
* @brief Wait��Ԃ̊Ǘ����\�b�h
*/
void Enemy::wait()
{
    // �s�� => �������Ȃ�
    //SetAnim(eEnemy::Idle);  // ���ꂪ�Ȃ���animTimer�����������A�ŏ��ł܂�

    // �J��
    /*
        �ړ��F
            �����F��莞�Ԃ̌o��
        �ǐՁF
            �����F����Ƀv���C���[������
    */
    count++;

    if (count > TIME_TO_TRANSITION)   // �J�ڃ^�C�}�[�𒴂����̂�Move��
    {
        count = 0;
        currentState = EnemyState::Move;
        angle = (rand() % FULL_CIRCLE_DEGREES);  // �����_���Ȋp�x���擾
        // �A�j���[�V�������Z�b�g
        setAnimationHandle(eEnemy::AnimationNum::Run);
        animTime = animTimes[static_cast<int>(eEnemy::AnimationNum::Run)];

    }
    // ����ɓ����Ă�����ǐ�
    else if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // �A�j���[�V�������Z�b�g
        setAnimationHandle(eEnemy::AnimationNum::Run);
        animTime = animTimes[static_cast<int>(eEnemy::AnimationNum::Run)];
    }

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
    VECTOR Vec = VGet(sinf(Rad), 0.f, cosf(Rad));
    // -1����Z���邱�ƂŃx�N�g�����t�]
    Vec = VScale(Vec, -1.f);

    // ���W�ύX
    // �x�N�g���̑傫������Z�A�ړ����x��
    Vec = VScale(Vec, ENEMY_MOVE_SPEED);
    // �ړ���܂ł̃x�N�g���擾
    VECTOR NewPos = VAdd(Vec, position);

    // ���Ƃ̓����蔻��@�������Ă��������
    if (pGame->GetCollision()->clampToStageBounds(NewPos, position)) 
    {
        // ����ɓ����Ă�����ǐ�        
        if (isTargetVisible() == true)
        {
            currentState = EnemyState::Chase;
        }
    }

    // �J��
    /*
        �ҋ@�F
            �����F��莞�Ԃ̌o��
        �ǐՁF
            �����F����Ƀv���C���[������
    */
    count++;

    if (count >= TIME_TO_TRANSITION)     // �J�ڃ^�C�}�[�𒴂����̂�Wait��
    {
        count = 0;
        currentState = EnemyState::Wait;
        // �A�j���[�V�������Z�b�g
        setAnimationHandle(eEnemy::AnimationNum::Idle);
        animTime = animTimes[static_cast<int>(eEnemy::AnimationNum::Idle)];
    }
    // ����ɓ����Ă�����ǐ�
    else if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // �A�j���[�V�����͂��ł�Run�Ȃ̂ŕύX�Ȃ�
    }

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
    VECTOR Velocity = VScale(Direction, ENEMY_MOVE_SPEED);

    // �ړ���܂ł̃x�N�g���擾
    VECTOR NewPos = VAdd(Velocity, position);

    // ���Ƃ̓����蔻��
    pGame->GetCollision()->clampToStageBounds(NewPos, position);

    // �t�O�p�֐����g�p�@�x�N�g������G�l�~�[�ɑ΂���v���C���[�̊p�x�����߂�
    angle = atan2f(-Velocity.x, -Velocity.z);

    // �J��
    /*
        �ҋ@�F
            �����F�v���C���[�����삩��o��
    */
    if (isTargetVisible() == false)
    {
        currentState = EnemyState::Wait;
        count = 0;
        setAnimationHandle(eEnemy::AnimationNum::Idle);
        animTime = animTimes[static_cast<int>(eEnemy::AnimationNum::Idle)];
    }
}


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
    if (hitPoint <= 0)
    {
        return false;
    }

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
