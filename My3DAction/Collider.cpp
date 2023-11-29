#include "Collider.h"
#include "Player.h"
#include "Enemy.h"


/**
* @brief Camera�̃R���X�g���N�^
*
*/
Collider::Collider()
{

}


// �f�X�g���N�^��
Collider::~Collider()
{

}


// �L�������m�̓����蔻��
void Collider::Chara_Collision(VECTOR* player, Enemy* enemy, VECTOR* moveVec)
{
	VECTOR ChkChToChVec;
	VECTOR PushVec;
	VECTOR ChPosition;
	float Length;

	// �ړ���� ch �̍��W���Z�o
	ChPosition = VAdd(*player, *moveVec);

	// 
	if (HitCheck_Capsule_Capsule(
		ChPosition, VAdd(ChPosition, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH,
		enemy->position, VAdd(enemy->position, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH) == TRUE)
	{
		// �������Ă�����v���C���[�����߂�

		// chk_ch ���� ch �ւ̃x�N�g�����Z�o
		ChkChToChVec = VSub(ChPosition, enemy->position);

		// �x���͌��Ȃ�
		ChkChToChVec.y = 0.f;

		// ��l�̋������Z�o
		Length = VSize(ChkChToChVec);

		// chk_ch ���� ch �ւ̃x�N�g���𐳋K��( �x�N�g���̒����� 1.0f �ɂ��� )
		PushVec = VScale(ChkChToChVec, 1.0f / Length);

		// �����o���������Z�o�A������l�̋��������l�̑傫�����������l�ɉ����o���͂𑫂��ė���Ă��܂��ꍇ�́A�҂����肭���������Ɉړ�����
		if (Length - CHARA_HIT_WIDTH * 2.0f + CHARA_HIT_PUSH_POWER > 0.0f)
		{
			float TempY;

			TempY = ChPosition.y;
			ChPosition = VAdd(*player, VScale(PushVec, CHARA_HIT_WIDTH * 2.0f));

			// �x���W�͕ω������Ȃ�
			ChPosition.y = TempY;
		}
		else
		{
			// �����o��
			ChPosition = VAdd(ChPosition, VScale(PushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
	*moveVec = VSub(ChPosition, *player);


}



// 
void Collider::draw(VECTOR start, VECTOR end, float radius, int polygon, int difColor, int spcColor, int flag)
{

	VECTOR dir = VSub(end, start);
	float length = VSize(dir);

	// �J�v�Z�����S��
	DrawLine3D(start, end, difColor);

	// ���W ( 320.0f, 100.0f, 0.0f ) �� ( 320.0f, 300.0f, 0.0f ) ���Q�_�Ƃ���
    // ���a 40.0f �̃J�v�Z����`�悷��
	// DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(255, 255, 0), FALSE);
	
	// �J�v�Z���̏㔼��
	DrawCapsule3D(start, VGet(length / 2, 0.f, 0.f), radius, polygon, difColor, spcColor, flag);

	// �J�v�Z���̉�����
	DrawCapsule3D(end, VGet(length / 2, 0.f, 0.f), radius, polygon, difColor, spcColor, flag);

}