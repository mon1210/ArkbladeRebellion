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
        animHandle = pGame->GetModelManager()->GetEnemyModel();
        tileHandle = pGame->GetBG()->GetModelHandle();
    }

    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, eEnemy::Idle);

}


// �f�X�g���N�^
Enemy::~Enemy()
{
}


/**
* @brief �A�j���[�V������ԏ������֐�
* @note  Stage�ŏ���������x�����Ăяo��
*/
void Enemy::initAnimation()
{
    animationHandle(eEnemy::Idle);

}


/**
* @brief �A�j���[�V������ݒ肷��
* @param[in] num    �A�j���[�V�����ԍ�
*/
void Enemy::animationHandle(eEnemy::AnimationNum num) {
    // �A�j���[�V�������Z�b�g
    if (animNo != num)  // �������Ȃ���animTimer�����܂����Z�b�g����Ȃ�
    {
        animNo = num;
        setAnim(animHandle, animNo, animTime, animTimer);
    }
};


/**
* @brief enemyToPlayer�̍X�V�E�������Z�o�@���t���[���Ăяo��
* @note  ���t���[���̏���
*/
void Enemy::updateEnemyToPlayerVec() 
{
    enemyToPlayer = VSub(pGame->GetPlayer()->GetPos(), position);   // �G�l�~�[����v���C���[�̋����x�N�g�������߂�
    vecLength = sqrtf(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.z * enemyToPlayer.z); // �����x�N�g���̒���
}


/**
* @brief �s����Ԃ̊Ǘ����\�b�h
* @note  ���t���[���̏���
*/
void Enemy::update()
{
    switch (currentState)
    {
    case EnemyState::Wait:
        Wait();
        break;
    case EnemyState::Move:
        Move();
        break;
    case EnemyState::Chase:
        Chase();
        break;
    //case EnemyState::Attack:
    //    break;
    //case EnemyState::Damage:
    //    break;
    //case EnemyState::Death:
    //    break;
    }
    // enemy��player�̋����x�N�g���̍X�V
    updateEnemyToPlayerVec();

    // Rader��Point�ɒǉ�
    pGame->GetRadar()->addPoint(position.x, position.z, eRadar::Enemy);

    // �A�j���[�V�����^�C�}�[���Z�b�g
    if (updateAnimation(animTime, animTimer, ENEMY_ANIM_F_INCREMENT))
        animTimer = 0.f;

}


/**
* @brief Wait��Ԃ̊Ǘ����\�b�h
*/
void Enemy::Wait()
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
        animationHandle(eEnemy::Run);

    }
    // ����ɓ����Ă�����ǐ�
    else if (isTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // �A�j���[�V�������Z�b�g
        animationHandle(eEnemy::Run);
    }

}


/**
* @brief Move��Ԃ̊Ǘ����\�b�h
*/
void Enemy::Move()
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

    NewPos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
    // MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
    MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(
        tileHandle,				                             // ����ΏۂƂȂ郂�f���̃t���[��
        -1,												        // �ΏۂƂȂ�t���[���ԍ�
        NewPos,										        // Ray�̎n�_   ���f���̑���
        VGet(NewPos.x, NewPos.y - CHARA_HEIGHT, NewPos.z)	// Ray�̏I�_   ���f���̓���
    );

    if (Result.HitFlag == 1) // ������`�F�b�N
    {
        // HitPosition => ��_�̍��W
        NewPos.y = Result.HitPosition.y;
        position = NewPos;
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
        animationHandle(eEnemy::Idle);
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
void Enemy::Chase()
{
    // �s���F������̃v���C���[��ǂ�������
    
    // ������0�ȉ��̎��͉������Ȃ�   // �قڒʂ�Ȃ�
    if (vecLength <= 0.f) { return; }

    // �x�N�g����P�ʃx�N�g����
    VECTOR Direction = VGet(enemyToPlayer.x / vecLength, 0.f, enemyToPlayer.z / vecLength);

    // �P�ʃx�N�g�����X�J���[�{�A�ړ����x��
    VECTOR Velocity = VScale(Direction, ENEMY_MOVE_SPEED);

    // �ړ���܂ł̃x�N�g���擾
    VECTOR NewPos = VAdd(Velocity, position);

    //VECTOR playerPos = pGame->GetPlayer()->getPos();
    //pGame->GetCollision()->charaCapCol(position, new_pos, playerPos, CAP_HEIGHT, CAP_HEIGHT, ENEMY_CAP_RADIUS, PLAYER_CAP_RADIUS);

    NewPos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
    // MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
    MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(
        tileHandle,				                                // ����ΏۂƂȂ郂�f���̃t���[��
        -1,												        // �ΏۂƂȂ�t���[���ԍ�
        NewPos,										        // Ray�̎n�_   ���f���̑���
        VGet(NewPos.x, NewPos.y - CHARA_HEIGHT, NewPos.z)	// Ray�̏I�_   ���f���̓���
    );

    if (Result.HitFlag == 1) // ������`�F�b�N
    {
        // HitPosition => ��_�̍��W
        NewPos.y = Result.HitPosition.y;
        // if(length >= ENEMY_SPEED)
        position = NewPos;
    }

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
        animationHandle(eEnemy::Idle);
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
}


/**
* @brief �G�l�~�[���W���擾���ĕԂ�
*/
VECTOR Enemy::GetPos()
{
    return  position;
}