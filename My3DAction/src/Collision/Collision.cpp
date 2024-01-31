#include "Collision.h"

/**
* @brief Collision�̃R���X�g���N�^
*/
Collision::Collision(Game *Game_)
{
	pGame = Game_;

	if (pGame)
		tileHandle = pGame->GetBG()->GetModelHandle();
}


// �f�X�g���N�^
Collision::~Collision()
{
}


/**
* @brief �����蔻�菉����
* @note  ���ɓ����蔻��t�^
*/
void Collision::initialize(int handle)
{
	// Tile�ɓ����蔻��t�^
	MV1SetupCollInfo(
		handle = 0,		// �����蔻���ݒ肷�郂�f���̃n���h��
		-1,					// �ΏۂƂȂ郂�f���̃t���[���ԍ�(-1�͑S��)	
		SPATIAL_PARTITION,	// X���̋�ԕ�����
		SPATIAL_PARTITION,	// Y���̋�ԕ�����
		SPATIAL_PARTITION	// Z���̋�ԕ�����
	);
}


/**
* @brief  �ړ����̃X�e�[�W�Ƃ̓����蔻�胁�\�b�h
* @note   �ړ��͈͂𐧌����Ă���
* @return true:���肠��A�ړ��� / false:����Ȃ��A�ړ��s��
*/
bool Collision::clampToStageBounds(VECTOR& new_pos, VECTOR& pos)
{
	new_pos.y += 1.0f;  // ���ꂪ�Ȃ��ƍ��E,���Ɉړ��ł��Ȃ�
	// MV1_COLL_RESULT_POLY => �����蔻��̌��ʏ�񂪕ۑ����ꂽ�\����
	MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(
		tileHandle,												// ����ΏۂƂȂ郂�f���̃t���[��
		-1,														// �ΏۂƂȂ�t���[���ԍ�
		new_pos,												// Ray�̎n�_   ���f���̑���
		VGet(new_pos.x, new_pos.y - CHARA_HEIGHT, new_pos.z)	// Ray�̏I�_   ���f���̓���
	);

	if (Result.HitFlag == 1) // ������`�F�b�N
	{
		// HitPosition => ��_�̍��W
		new_pos.y = Result.HitPosition.y;
		pos = new_pos;
		return true;
	}
	else
	{
#ifdef _DEBUG
		// ������Ȃ������ꍇ�͏Փ˂��Ȃ������|��`��
		DrawString(0, 0, "NO HIT", BLUE);
#endif // !_DEBUG

		return false;
	}

}


/**
* @brief  �L�������m�̃J�v�Z�������蔻�胁�\�b�h
* @note   �L�����̈ړ����ɌĂяo���Ă���
* @return true:�������Ă��� / false:�������Ă��Ȃ�
* @param[in] pos1�@			�ړ����Ă���L�����̍��W
* @param[in] pos1_move_vec�@�ړ����Ă���L�����̈ړ��x�N�g��
* @param[in] pos2�@			�������鑤�̍��W
* @param[in] cap1_height�@	pos1�̃J�v�Z���̍���
* @param[in] cap2_height�@	pos2�̃J�v�Z���̍���
* @param[in] cap1_radius�@	pos1�̃J�v�Z���̔��a
* @param[in] cap2_radius�@	pos2�̃J�v�Z���̔��a
*/
bool Collision::charaCapCol(VECTOR& pos1, VECTOR& pos1_move_vec, VECTOR pos2, float cap1_height, float cap2_height, float cap1_radius, float cap2_radius)
{
	// �ړ���� ch �̍��W���Z�o
	VECTOR NewPos1 = VAdd(pos1, pos1_move_vec);

	// ��̃J�v�Z���œ����蔻��
	if (HitCheck_Capsule_Capsule(
		pos1, VGet(pos1.x, pos1.y + cap1_height, pos1.z), cap1_radius,
		pos2, VGet(pos2.x, pos2.y + cap2_height, pos2.z), cap2_radius) == TRUE)
	{
		// pos2 ���� pos1 �ւ̃x�N�g�����Z�o
		VECTOR Pos2ToPos1Vec = VSub(NewPos1, pos2);

		// �x���͌��Ȃ�
		Pos2ToPos1Vec.y = 0.f;

		// ��l�̋������Z�o
		float Length = VSize(Pos2ToPos1Vec);

		// pos2 ���� pos1 �ւ̃x�N�g���𐳋K��( �x�N�g���̒����� 1.0f �ɂ��� )
		VECTOR PushVec = VScale(Pos2ToPos1Vec, 1.f / Length);

		// �����o���������Z�o ------
		// ��l�̋��������l�̑傫�����������l�ɉ����o���͂𑫂��Ă�����Ă��܂��ꍇ�́A�҂����肭���������Ɉړ�����
		if (Length - (cap2_radius * 2.f) + CHARA_HIT_PUSH_POWER > 0.f)	// * 2.f => ���a�����߂�
		{
			float TempY;		// �R�s�[�p

			TempY = NewPos1.y;	// Y�����R�s�[
			NewPos1 = VAdd(pos1, VScale(PushVec, cap2_radius * 2.f));

			// Y���W�͕ω������Ȃ�
			NewPos1.y = TempY;
			// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
			pos1_move_vec = VSub(NewPos1, pos1);
		}
		else
		{
			// �����o��
			NewPos1 = VAdd(NewPos1, VScale(PushVec, CHARA_HIT_PUSH_POWER));
			// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
			pos1_move_vec = VSub(NewPos1, pos1);
		}

		return true;
	}
	// �������Ă��Ȃ�
	else
	{
		// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
		pos1_move_vec = VSub(NewPos1, pos1);
		return false;
	}

	return false;
}


/**
* @brief  �L�����N�^�[���U���͈͓��ɂ��邩�����𔻒肷�郁�\�b�h
* @note   
* @return true:�U���͈͂̒� / false:�U���͈͂̊O
* @param[in] attack_ch_pos�@�U�����悤�Ƃ��Ă���L�����̍��W
* @param[in] damage_ch_pos�@�U�����󂯂悤�Ƃ��Ă���L�����̍��W
* @param[in] attack_area�@	�U���͈�
*/
bool Collision::checkAttackArea(VECTOR attack_ch_pos, VECTOR damage_ch_pos, float attack_area)
{
	// �U���傩�瑊��܂ł̈ʒu�𑪂�
	float DistanceLength = VSize(VSub(attack_ch_pos, damage_ch_pos));

	// �L�����̋������U���͈͂�菬����������
	if (attack_area >= DistanceLength)
	{
		return true;
	}

	return false;
}


/**
* @brief  ��������₪�A���������ǂ����𔻒f
* @note	  OBB�̓��e�����Ɠ�̋�����r
* 
* @return true:�������ł��� / false:�������ł͂Ȃ�
* @param[in] axis�@			���������
* @param[in] obb1_vertices�@��ڂ�OBB�̒��_
* @param[in] obb2_vertices�@��ڂ�OBB�̒��_
*/
bool Collision::isFindSeparatingAxis(const VECTOR& axis, VECTOR obb1_vertices[8], VECTOR obb2_vertices[8])
{
	// �eOBB���_���X�g
	VECTOR* vertices_list[2] = 
	{
		obb1_vertices,
		obb2_vertices
	};

	// �ˉe���ꂽ���_�̍ŏ��l�ƍő�l���Ǘ�
	struct Length
	{
		float min = 10000.f;	// �傫�Ȓl�ŏ��������Ȃ��ƍX�V����Ȃ�
		float max = -10000.f;	// �����Ȓl�ŏ��������Ȃ��ƍX�V����Ȃ�
	};
	// 2�{��
	Length length[2];

	// 2 = vertices_list.size
	for (int i = 0; i < 2; i++)
	{
		// 8 = �eOBB�̒��_��
		for (int j = 0; j < 8; j++)
		{
			// [0][0] => [��ڂ�OBB][��ڂ̒��_]
			VECTOR vertice = vertices_list[i][j];
			// ��axis�ƒ��_�Ƃ̓��ς��Ƃ�
			// (�����̃x�N�g��)���ɋ�`�̒��_���ˉe���čŏ��A�ő�����߂�
			float dot = axis.x * vertice.x + axis.y * vertice.y + axis.z * vertice.z;

			// ��������ōł��������_�܂ł̋��������߂�

			// �ŏ��l�X�V
			if (length[i].min > dot)
			{
				length[i].min = dot;
			}
			// �ő�l�X�V
			if (length[i].max < dot)
			{
				length[i].max = dot;
			}
		}
	}

	// �������Ă���Ƃ�	�������ł͂Ȃ�
	if (length[0].min <= length[1].max && length[1].min <= length[0].max)
	{
		return false;
	}

	return true;
}


