#include <math.h>
#include "Enemy.h"

/**
* @brief Enemy�̃R���X�g���N�^
*
*/
Enemy::Enemy()
{
    animNo = 0;
    count = 0;
    animHandle = 0;
    tileHandle = 0;
    animTime = 0.f;
    animTimer = 0.f;
    hitPoint = 1.f;
    animTimer = 0.f;
    vecLength = 0.f;

    enemyToPlayer = VGet(0.f, 0.f, 0.f);
    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);
    playerPos = VGet(0.f, 0.f, 0.f);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    currentState = EnemyState::Wait;

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
void Enemy::InitAnimation()
{
    SetAnim(eEnemy::Idle);
}


/**
* @brief �s����Ԃ̊Ǘ����\�b�h
* @note  ���t���[���̏���
*/
void Enemy::Update()
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

    // Rader


    // �`�惁�\�b�h�Ăяo��
    draw();
}


/**
* @brief Wait��Ԃ̊Ǘ����\�b�h
* 
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
        SetAnim(eEnemy::Run);

    }
    // ����ɓ����Ă�����ǐ�
    else if (IsTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        SetAnim(eEnemy::Run);
    }

}


/**
* @brief �����f�����Z�b�g����
*
*/
void Enemy::setTileModel(int model)
{
    tileHandle = model;
}


/**
* @brief Move��Ԃ̊Ǘ����\�b�h
*
*/
void Enemy::Move()
{
    // �s���F�܂������i��(�X�e�[�W��̎�)
    // �x�N�g���Z�o
    float rad = angle * DX_PI_F / 180.f;
    // �O�����x�N�g���̐���
    VECTOR vec = VGet(sinf(rad), 0.f, cosf(rad));
    // -1����Z���邱�ƂŃx�N�g�����t�]
    vec = VScale(vec, -1.f);

    // ���W�ύX
    // �x�N�g���̑傫������Z�A�ړ����x��
    vec = VScale(vec, ENEMY_MOVE_SPEED);
    // �ړ���܂ł̃x�N�g���擾
    VECTOR new_pos = VAdd(vec, position);

    new_pos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
    // MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
    MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
        tileHandle,				                         // ����ΏۂƂȂ郂�f���̃t���[��
        -1,												// �ΏۂƂȂ�t���[���ԍ�
        new_pos,										// Ray�̎n�_   ���f���̑���
        VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Ray�̏I�_   ���f���̓���
    );

    if (result.HitFlag == 1) // ������`�F�b�N
    {
        // HitPosition => ��_�̍��W
        new_pos.y = result.HitPosition.y;
        position = new_pos;
        if (IsTargetVisible() == true)
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
        SetAnim(eEnemy::Idle);
    }
    // ����ɓ����Ă�����ǐ�
    else if (IsTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        // �A�j���[�V�����͂��ł�Run�Ȃ̂ŕύX�Ȃ�
    }

}


/**
* @brief Chase��Ԃ̊Ǘ����\�b�h
*
*/
void Enemy::Chase()
{
    // �s���F������̃v���C���[��ǂ�������
    
    // ������0�ȉ��̎��͉������Ȃ�   // �قڒʂ�Ȃ�
    if (vecLength <= 0.f) { return; }

    // �x�N�g����P�ʃx�N�g����
    VECTOR direction = VGet(enemyToPlayer.x / vecLength, 0.f, enemyToPlayer.z / vecLength);

    // �P�ʃx�N�g�����X�J���[�{�A�ړ����x��
    VECTOR velocity = VScale(direction, ENEMY_MOVE_SPEED);

    VECTOR new_pos = VAdd(velocity, position);
    new_pos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
    // MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
    MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
        tileHandle,				                       // ����ΏۂƂȂ郂�f���̃t���[��
        -1,												// �ΏۂƂȂ�t���[���ԍ�
        new_pos,										// Ray�̎n�_   ���f���̑���
        VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Ray�̏I�_   ���f���̓���
    );

    if (result.HitFlag == 1) // ������`�F�b�N
    {
        // HitPosition => ��_�̍��W
        new_pos.y = result.HitPosition.y;
        // if(length >= ENEMY_SPEED)
        position = new_pos;
    }

    // �t�O�p�֐����g�p�@�x�N�g������G�l�~�[�ɑ΂���v���C���[�̊p�x�����߂�
    angle = atan2f(-velocity.x, -velocity.z);

    // �J��
    /*
        �ҋ@�F
            �����F�v���C���[�����삩��o��
    */
    if (IsTargetVisible() == false)
    {
        currentState = EnemyState::Wait;
        count = 0;
        SetAnim(eEnemy::Idle);
    }
}


/**
* @brief �v���C���[�̍��W���Z�b�g����
*
*/
void Enemy::setPlayerPos(VECTOR player_pos)
{
    playerPos = player_pos;
}


/**
* @brief   �G�l�~�[�̎��상�\�b�h
* @return  true : ������Ƀv���C���[������ / false : ����O�Ƀv���C���[������ 
*/
bool Enemy::IsTargetVisible()
{
    /*
        �EEnemy�̍��W(x,z)���~�̒��S�Ƃ��čl����
        �EPlayer�̍��W��_�Ƃ��čl����
        �E�~�̔��a��10

        �_�Ɖ~�̓����蔻����g���A�_���~�̒��ɂ�������true
    
    */

    enemyToPlayer = VSub(playerPos, position);   // �G�l�~�[����v���C���[�̋����x�N�g��
    vecLength = sqrtf(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.z * enemyToPlayer.z);    // �����x�N�g���̒���

    float radius = 50.f;    // �~�̔��a

    // ���a���x�N�g�����Z���Ȃ�����true��Ԃ�
    if (vecLength <= radius)
    {
        return true;
    }
    
    return false;
}


/**
* @brief �G�l�~�[���f�����Z�b�g����
*
*/
void Enemy::setEnemyModel(int model)
{
    animHandle = model;
}


/**
* @brief �A�j���[�V�����Z�b�g�֐�
*
*/
void Enemy::SetAnim(eEnemy::AnimationNum num)
{
    if (animNo != num)
    {
        animNo = num;
        animTimer = 0;
        // �A�j���[�V�����ɂ����鎞�Ԃ��擾
        animTime = MV1GetAnimTotalTime(animHandle, animNo);
        // �A�j���[�V�������f�^�b�`
        MV1DetachAnim(animHandle, 0);
        // �A�j���[�V�������A�^�b�`
        MV1AttachAnim(animHandle, animNo);
    }

}


/**
* @brief �G�l�~�[�̃A�j���[�V�������\�b�h
* @return true:���� / false:���S
* @note �����ł͉����x�̐ݒ肾���s���A(x, y)���W�̍X�V��collide() �ōs��
*/
bool Enemy::move()
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
    animTimer += ENEMY_ANIM_F_INCREMENT;
    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
    if (animTimer >= animTime)
    {
        animTimer = 0.0f;
    }
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
* @note
*/
VECTOR Enemy::GetEnemyPos()
{
    return  position;
}