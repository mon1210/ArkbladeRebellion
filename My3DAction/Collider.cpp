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
void Collider::Chara_Collision(Player* player, Enemy* enemy)
{
	VECTOR ChkChToChVec;
	VECTOR PushVec;
	float Length;

	// 
	if (HitCheck_Capsule_Capsule(
		player->position, VAdd(player->position, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH,
		enemy->position, VAdd(enemy->position, VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH) == TRUE)
	{
		// �������Ă�����v���C���[�����߂�

		// chk_ch ���� ch �ւ̃x�N�g�����Z�o
		ChkChToChVec = VSub(player->position, enemy->position);

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

			TempY = player->position.y;
			player->position = VAdd(player->position, VScale(PushVec, CHARA_HIT_WIDTH * 2.0f));

			// �x���W�͕ω������Ȃ�
			player->position.y = TempY;
		}
		else
		{
			// �����o��
			player->position = VAdd(player->position, VScale(PushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
	// *ch_MoveVec = VSub(player->position, ch->Position);


}



// 
void Collider::draw()
{

}