#include "Collider.h"

/**
* @brief Camera�̃R���X�g���N�^
*
*/
Collider::Collider()
{
	tileHandle = 0;
}


// �f�X�g���N�^
Collider::~Collider()
{
}


/**
* @brief �����蔻�菉����
* @note  ���ɓ����蔻��t�^
*/
void Collider::InitCollision(int handle)
{
	// Tile�ɓ����蔻��t�^
	MV1SetupCollInfo(
		handle = 0,			// �����蔻���ݒ肷�郂�f���̃n���h��
		-1,					// �ΏۂƂȂ郂�f���̃t���[���ԍ�(-1�͑S��)	
		32,					// X���̋�ԕ�����
		32,					// Y���̋�ԕ�����
		32					// Z���̋�ԕ�����
	);
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
		enemy->GetEnemyPos(), VAdd(enemy->GetEnemyPos(), VGet(0.f, CHARA_HIT_HEIGHT, 0.f)), CHARA_HIT_WIDTH) == TRUE)
	{
		// �������Ă�����v���C���[�����߂�

		// chk_ch ���� ch �ւ̃x�N�g�����Z�o
		ChkChToChVec = VSub(ChPosition, enemy->GetEnemyPos());

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


/**
* @brief �����f�����Z�b�g����
*/
void Collider::setTileModel(int model)
{
	tileHandle = model;
}


/**
* @brief �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
* @note  Player�N���X�ŌĂяo��
*		 �v���C���[�̈ړ��͈͂𐧌����Ă���
*/
void Collider::ClampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able)
{
	new_pos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
	// MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
	MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
		tileHandle,									    // ����ΏۂƂȂ郂�f���̃t���[��
		-1,												// �ΏۂƂȂ�t���[���ԍ�
		new_pos,										// Ray�̎n�_   ���f���̑���
		VGet(new_pos.x, new_pos.y - 250.f, new_pos.z)	// Ray�̏I�_   ���f���̓���
	);

	if (result.HitFlag == 1) // ������`�F�b�N
	{
		// HitPosition => ��_�̍��W
		new_pos.y = result.HitPosition.y;
		player_pos = new_pos;
		roll_able = true;
		// ���������Ƃ��ɂ��̎|��`��
		DrawString(0, 0, "HIT", GetColor(255, 0, 0));
	}
	else
	{
		// �X�e�[�W�[������Roll�ł��Ȃ��悤��
		roll_able = false;
		// ������Ȃ������ꍇ�͏Փ˂��Ȃ������|��`��
		DrawString(0, 0, "NO HIT", GetColor(0, 0, 255));
	}

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