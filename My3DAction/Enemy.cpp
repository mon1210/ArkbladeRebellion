#include "Enemy.h"
#include "Constants.h"
#include "Model.h"
#include "Enums.h"


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
    angle = ENEMY_START_ROTATE_Y;

    position = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y, ENEMY_START_POS_Z);

    animTime = MV1GetAnimTotalTime(animHandle, 0);

    pModel = new Model();

    // ���f���擾
    pModel->LoadEnemyModel();
    animHandle = pModel->GetEnemyModel();

    // ���f����Idle�A�j���[�V�������Z�b�g
    MV1AttachAnim(animHandle, eEnemy::Idle);


}


// �f�X�g���N�^
Enemy::~Enemy()
{
    SAFE_DELETE(pModel);
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
    SetMove();

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