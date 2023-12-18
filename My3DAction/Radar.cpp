#include "Radar.h"


/**
* @brief Radar�̃R���X�g���N�^
*/
Radar::Radar()
{
}


// �f�X�g���N�^
Radar::~Radar()
{
}


/**
* @brief �`�惁�\�b�h
*/
void Radar::draw()
{
	// Rader�\��
	// UI�̉~��(������)
	DrawCircle(uiPosX, uiPosY, radius, BLACK, TRUE);
	// UI�̉~�̕�(��������)
	DrawCircle(uiPosX, uiPosY, radius, WHITE, FALSE);

	// Radar�f�[�^���
	RadarData RadarData
	{
		uiPosX,
		uiPosY,
		centerX,
		centerZ,
		frontVecX,
		frontVecZ,
		radius

	};

	// Point�̐����A�`�惁�\�b�h�Ăяo��
	for (auto& point : pointList)
	{
		point.draw(RadarData);
	}
}


/**
* @brief Point��ǉ����郁�\�b�h
* @note  ���W�擾���K�v�Ȃ̂Ŗ��t���[���Ăяo��
*		 RadarPoint�̃R���X�g���N�^�Ăяo��
* @param[in] x�@	x���W
* @param[in] z�@	z���W
* @param[in] type_	Point�̎�ށ@����Point�\���Ă��邩
*/
void Radar::addPoint(float x, float z, eRadar::PointType type_)
{
	// �����̕�����v�f���\�z�@push_back�Ƃقړ��`
	pointList.emplace_back(x, z, type_);
}


/**
* @brief Radar�̒��S���̂�ݒ肷�郁�\�b�h
* @note  ���W�擾���K�v�Ȃ̂Ŗ��t���[���Ăяo��
*		 Player�����S�Ȃ̂�Player�ŌĂяo���Ă���
* @param[in] x�@			���S���̂�x���W
* @param[in] z�@			���S���̂�z���W
* @param[in] front_vec_x	���S���̂̑O���x�N�g��X
* @param[in] front_vec_z	���S���̂̑O���x�N�g��Z
*/
void Radar::addCenter(float x, float z, float front_vec_x, float front_vec_z)
{
	centerX = x;
	centerZ = z;

	frontVecX = front_vec_x;
	frontVecZ = front_vec_z;
}


/**
* @brief Point��List�����������郁�\�b�h
* @note  ���t���[���ŏ��ɌĂяo��
*/
void Radar::listReset()
{
	// ���X�g���̗v�f���폜
	pointList.clear();
}