#include "Collision.h"

/**
* @brief Collision�̃R���X�g���N�^
*/
Collision::Collision(Game *Game_)
{
	pGame = Game_;

	if (pGame)
		tileHandle = pGame->GetModelManager()->getTileModel();

}


// �f�X�g���N�^
Collision::~Collision()
{
}


/**
* @brief �����蔻�菉����
* @note  ���ɓ����蔻��t�^
*/
void Collision::initCollision(int handle)
{
	// Tile�ɓ����蔻��t�^
	MV1SetupCollInfo(
		handle = 0,			// �����蔻���ݒ肷�郂�f���̃n���h��
		-1,					// �ΏۂƂȂ郂�f���̃t���[���ԍ�(-1�͑S��)	
		SPATIAL_PARTITION,	// X���̋�ԕ�����
		SPATIAL_PARTITION,	// Y���̋�ԕ�����
		SPATIAL_PARTITION	// Z���̋�ԕ�����
	);
}


/**
* @brief �v���C���[�ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
* @note  Player�N���X�ŌĂяo��
*		 �v���C���[�̈ړ��͈͂𐧌����Ă���
*/
void Collision::clampToStageBounds(VECTOR& new_pos, VECTOR& player_pos, bool& roll_able)
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


/**
* @brief �f�o�b�O�p�@�L�������m�̃J�v�Z���`�惁�\�b�h
* @note  Game�Ŗ��t���[���Ăяo���Ă���
*/
void Collision::debugCapColDraw()
{
	// player
	VECTOR Pos = pGame->GetPlayer()->getPos();
	DrawCapsule3D(Pos, VGet(Pos.x, Pos.y + CAP_HEIGHT, Pos.z), PLAYER_CAP_RADIUS, 10, RED, RED, FALSE);
	// enemy
	VECTOR ePos = pGame->GetEnemy()->getPos();
	DrawCapsule3D(ePos, VGet(ePos.x, ePos.y + CAP_HEIGHT, ePos.z), ENEMY_CAP_RADIUS, 10, RED, RED, FALSE);
}


/**
* @brief �L�������m�̃J�v�Z�������蔻�胁�\�b�h
* @note  player�̈ړ����ɌĂяo���Ă���
* @param[in] pos1�@			�ړ����Ă���L�����̍��W
* @param[in] pos1_move_vec�@�ړ����Ă���L�����̈ړ��x�N�g��
* @param[in] pos2�@			�������鑤�̍��W
* @param[in] CAP1_HEIGHT�@	pos1�̃J�v�Z���̍���
* @param[in] CAP2_HEIGHT�@	pos2�̃J�v�Z���̍���
* @param[in] CAP1_RADIUS�@	pos1�̃J�v�Z���̔��a
* @param[in] CAP2_RADIUS�@	pos2�̃J�v�Z���̔��a
*/
void Collision::charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR& pos2, float CAP1_HEIGHT, float CAP2_HEIGHT, float CAP1_RADIUS, float CAP2_RADIUS)
{

	// �ړ���� ch �̍��W���Z�o
	VECTOR NewPos1 = VAdd(pos1, pos1_move_vec);

	// ��̃J�v�Z���œ����蔻��
	if (HitCheck_Capsule_Capsule(
		pos1, VGet(pos1.x, pos1.y + CAP1_HEIGHT, pos1.z), CAP1_RADIUS,
		pos2, VGet(pos2.x, pos2.y + CAP2_HEIGHT, pos2.z), CAP2_RADIUS) == TRUE)
	{
		// pos2 ���� pos1 �ւ̃x�N�g�����Z�o
		VECTOR Pos2ToPos1Vec = VSub(NewPos1, pos2);

		// �x���͌��Ȃ�
		Pos2ToPos1Vec.y = 0.f;

		// ��l�̋������Z�o
		float length = VSize(Pos2ToPos1Vec);

		// pos2 ���� pos1 �ւ̃x�N�g���𐳋K��( �x�N�g���̒����� 1.0f �ɂ��� )
		VECTOR pushVec = VScale(Pos2ToPos1Vec, 1.f / length);

		// �����o���������Z�o ------
		// ��l�̋��������l�̑傫�����������l�ɉ����o���͂𑫂��Ă�����Ă��܂��ꍇ�́A�҂����肭���������Ɉړ�����
		if (length - (CAP2_RADIUS * 2.f) + CHARA_HIT_PUSH_POWER > 0.f)	// * 2.f => ���a�����߂�
		{
			float TempY;	// �R�s�[�p

			TempY = NewPos1.y;	// Y�����R�s�[
			NewPos1 = VAdd(pos1, VScale(pushVec, CAP2_RADIUS * 2.f));

			// Y���W�͕ω������Ȃ�
			NewPos1.y = TempY;

		}
		else
		{
			// �����o��
			NewPos1 = VAdd(NewPos1, VScale(pushVec, CHARA_HIT_PUSH_POWER));
		}
	}

	// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
	pos1_move_vec = VSub(NewPos1, pos1);

}