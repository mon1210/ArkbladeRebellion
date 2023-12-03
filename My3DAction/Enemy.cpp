#include <math.h>
#include "Enemy.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"
#include "BG.h"
#include "Player.h"


/**
* @brief Enemy�̃R���X�g���N�^
*
*/
Enemy::Enemy()
{
    animNo = 0;
    animTime = 0.f;
    animTimer = 0.f;
    hitPoint = 1.f;
    animTimer = 0.f;
    pModel = NULL;
    pBG = NULL;
    pPlayer = NULL;
    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    currentState = EnemyState::Wait;

    pBG = new BG();
    pModel = new Model();
    pPlayer = new Player();
    // ���f���擾
    pModel->LoadEnemyModel();
    animHandle = pModel->GetEnemyModel();

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, eEnemy::Idle);


}


// �f�X�g���N�^
Enemy::~Enemy()
{
    SAFE_DELETE(pBG);
    SAFE_DELETE(pPlayer);
    SAFE_DELETE(pModel);
}


/**
* @brief �A�j���[�V������ԏ������֐�
* @note  My3DAction.cpp�ň�񂾂��Ăяo��
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
    SetAnim(eEnemy::Idle);  // ���ꂪ�Ȃ���animTimer�����������A�ŏ��ł܂�

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
        angle = (rand() % 360);  // �����_���Ȋp�x���擾
        SetAnim(eEnemy::Run);

    }
    // ����ɓ����Ă�����ǐ�
    else if (IsTargetVisible() == true)
    {
        currentState = EnemyState::Chase;
        SetAnim(eEnemy::Run);
    }

}


// 
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
    //float move_speed = 0.1f;
    // �x�N�g���̑傫������Z�A�ړ����x��
    vec = VScale(vec, ENEMY_MOVE_SPEED);
    // �ړ���܂ł̃x�N�g���擾
    VECTOR new_pos = VAdd(vec, position);

    new_pos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
    // MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
    MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
        pBG->GetModelHandle(),				    // ����ΏۂƂȂ郂�f���̃t���[��
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


// 
void Enemy::Chase()
{
    // �s���F������̃v���C���[��ǂ�������
    // �G�l�~�[����v���C���[�̃x�N�g��(x,z�̂�)���Z�o
    // VECTOR player_pos = *pPlayer->GetPlayerPos();
    VECTOR enemy_to_player = VSub(/*player_pos*/*pPlayer->GetPlayerPos(), position);

    // �x�N�g���̒������Z�o
    float length = sqrt(enemy_to_player.x * enemy_to_player.x + enemy_to_player.z * enemy_to_player.z);
    // ������0�ȉ��̎��͉������Ȃ�
    if (length <= 0.f) { return; }

    // �x�N�g����P�ʃx�N�g����
    VECTOR direction = VGet(enemy_to_player.x / length, 0.f, enemy_to_player.z / length);

    // �P�ʃx�N�g�����X�J���[�{�A�ړ����x��
    VECTOR velocity = VScale(direction, ENEMY_MOVE_SPEED);

    VECTOR new_pos = VAdd(velocity, position);
    new_pos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
    // MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
    MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
        pBG->GetModelHandle(),				    // ����ΏۂƂȂ郂�f���̃t���[��
        -1,												// �ΏۂƂȂ�t���[���ԍ�
        new_pos,										// Ray�̎n�_   ���f���̑���
        VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Ray�̏I�_   ���f���̓���
    );

    if (result.HitFlag == 1) // ������`�F�b�N
    {
        // HitPosition => ��_�̍��W
        new_pos.y = result.HitPosition.y;
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


// 
bool Enemy::IsTargetVisible()
{
    /*
        �EEnemy�̍��W(x,z)���~�̒��S�Ƃ��čl����
        �EPlayer�̍��W��_�Ƃ��čl����
        �E�~�̔��a��10

        �_�Ɖ~�̓����蔻����g���A�_���~�̒��ɂ�������true
    
    */

    VECTOR vec = VSub(*pPlayer->GetPlayerPos(), position);   // �G�l�~�[����v���C���[�̋����x�N�g��
    float length = sqrtf(vec.x * vec.x + vec.z * vec.z);    // �����x�N�g���̒���

    float radius = 500.f;    // �~�̔��a

    // ���a���x�N�g�����Z���Ȃ�����true��Ԃ�
    if (length <= radius)
    {
        return true;
    }
    
    return false;
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
* @brief �s���Ǘ��֐�
* @Todo  �s���������_���ɂ������̂Ō�ŏ���
*/
void Enemy::SetMove()
{
    // I => Run���[�V����(2)
    if (CheckHitKey(KEY_INPUT_K))
    {
        SetAnim(eEnemy::Run);
        // ��O�ړ�
        if (animNo == eEnemy::Run)
        {
            angle = 0.f;
            position.z -= ENEMY_MOVE_SPEED;
        }
    }
    // 
    else if (CheckHitKey(KEY_INPUT_I))
    {
        SetAnim(eEnemy::Run);
        // ��O�ړ�
        if (animNo == eEnemy::Run)
        {
            angle = 180.f;
            position.z += ENEMY_MOVE_SPEED;
        }
    }
    // 
    else if (CheckHitKey(KEY_INPUT_O))
    {
        SetAnim(eEnemy::Swiping);
    }
    // 
    else if (CheckHitKey(KEY_INPUT_P))
    {
        SetAnim(eEnemy::Damage);
    }
    // 
    else if (CheckHitKey(KEY_INPUT_M))
    {
        SetAnim(eEnemy::Dying);
    }
    else
    {
        SetAnim(eEnemy::Idle);
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
    // �s���Ǘ��֐��Ăяo��
    //SetMove();

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
* @brief �G�l�~�[���W�擾�p�֐�
* @note
*/
VECTOR Enemy::GetEnemyPos()
{
    return  position;
}