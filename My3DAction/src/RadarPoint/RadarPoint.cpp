#include "RadarPoint.h"


// �R���X�g���N�^
RadarPoint::RadarPoint(float x, float z, eRadar::PointType type) 
	: posX(x), posZ(z), pointType(type)
{
}


// �f�X�g���N�^
RadarPoint::~RadarPoint()
{
}


// �`�惁�\�b�h
void RadarPoint::draw(RadarData& param)
{
	// center => Point�̍��W�ł̃x�N�g��
	float centerToPointVecX = posX - param.centerX;
	float centerToPointVecZ = posZ - param.centerZ;

	// �x�N�g���̒���
	float vecLength = sqrt(centerToPointVecX * centerToPointVecX + centerToPointVecZ * centerToPointVecZ);

	// ���������G�͈͊O�ɂȂ�����I��
	if (vecLength >= RADAR_DETECTION_RANGE)
		return;

	// point��center�ɗ�����(�����ʒu�ɗ�����) ���S��point�\��
	if (vecLength == 0.f)
	{
		DrawCircle(param.uiCenterX, param.uiCenterY, RADAR_POINT_RADIUS, RED);
		return;
	}


	// center => Point�̍��W�ł̃x�N�g���𐳋K��
	float normalizedVecX = centerToPointVecX / vecLength;	// X
	float normalizedVecZ = centerToPointVecZ / vecLength;	// Z

	//  center => Point�̒P�ʃx�N�g���ƁAfront�x�N�g���̓���(cos��)�����߂�
	float dotProduct = normalizedVecX * param.frontVecX + normalizedVecZ * param.frontVecZ;

	// cos�Ƃ��p�x�ɕύX
	float rad = acosf(dotProduct);


	// ���E���� ------------------------------------------
	//  center => Point�̃x�N�g���ƁAfront�x�N�g���̊O��(y�̂�)�����߂�
	float crossProductY = centerToPointVecX * param.frontVecZ - centerToPointVecZ * param.frontVecX;
	// crossProductY�����̒l�̎��Arad�𔽓]
	if (crossProductY < 0.f)
	{
		rad *= -1.f;
	}


	// �p�x����x�N�g�������߂�
	float newVecX = sinf(rad);
	float newVecZ = cosf(rad);


	// Rader�̍��G�͈͂Ɣ��a�̔䗦�����߂�
	float rate = param.raderRadius / RADAR_DETECTION_RANGE;


	// �䗦��center => point�̒�������Z�����l���x�N�g���̒����ɂ���
	newVecX *= rate * vecLength;
	newVecZ *= rate * vecLength;


	// Point�\��
	// �c���͏オ�u-�v�Ȃ̂ŁAz�̕�����ϊ�
	DrawCircle(param.uiCenterX + newVecX, param.uiCenterY - newVecZ, RADAR_POINT_RADIUS, RED);

}