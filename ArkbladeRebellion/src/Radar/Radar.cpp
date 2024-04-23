#include "Radar.h"


// �R���X�g���N�^
Radar::Radar()
{
}


// �f�X�g���N�^
Radar::~Radar()
{
}


// �`�惁�\�b�h
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


// Point��ǉ����郁�\�b�h
void Radar::addPoint(float x, float z, eRadar::PointType type_)
{
	// �����̕�����v�f���\�z
	pointList.emplace_back(x, z, type_);
}


// Radar�̒��S���̂�ݒ肷��
void Radar::addCenter(float x, float z, float front_vec_x, float front_vec_z)
{
	centerX = x;
	centerZ = z;

	frontVecX = front_vec_x;
	frontVecZ = front_vec_z;
}


// Point��List�����������郁�\�b�h
void Radar::listReset()
{
	// ���X�g���̗v�f���폜
	pointList.clear();
}