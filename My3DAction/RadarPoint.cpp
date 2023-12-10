#include "RadarPoint.h"


/**
* @brief RadarPoint�̃R���X�g���N�^
* @note  posX, posZ, pointType�͈����ŏ������A�Ăяo�����ɒl����������
* @param[in] x�@	x���W
* @param[in] z�@	z���W
* @param[in] type_	Point�̎�ށ@����Point�\���Ă��邩
*/
RadarPoint::RadarPoint(float x, float z, eRadar::PointType type_) 
	: posX(x), posZ(z), pointType(type_)
{
	centerToPointVecX = 0.f;
	centerToPointVecZ = 0.f;
	vecLength = 0.f;
	normalizedVecX = 0.f;
	normalizedVecZ = 0.f;
	rad = 0.f;
	dotProduct = 0.f;
	crossProductY = 0.f;
	newVecX = 0.f;
	newVecZ = 0.f;
	rate = 0.f;
}


// �f�X�g���N�^
RadarPoint::~RadarPoint()
{
}


/**
* @brief �`�惁�\�b�h
* @note  Radar�ŌĂяo��
* @param[in] param�@Radar�̃p�����[�^��ۑ������\����
*/
void RadarPoint::draw(RadarData& param)
{
	// center => Point�̍��W�ł̃x�N�g��
	centerToPointVecX = posX - param.centerX;
	centerToPointVecZ = posZ - param.centerZ;

	// �x�N�g���̒���
	vecLength = sqrt(centerToPointVecX * centerToPointVecX + centerToPointVecZ * centerToPointVecZ);

	// ���������G�͈͊O�ɂȂ�����I��	�����Ŏ~�܂��Ă���
	if (vecLength >= RADAR_DETECTION_RANGE)
		return;

	// point��center�ɗ�����(�����ʒu�ɗ�����) ���S��point�\��
	if (vecLength == 0.f)
	{
		DrawCircle(param.uiCenterX, param.uiCenterY, RADAR_POINT_RADIUS, RED);
		return;
	}


	// center => Point�̍��W�ł̃x�N�g���𐳋K��
	normalizedVecX = centerToPointVecX / vecLength;	// X
	normalizedVecZ = centerToPointVecZ / vecLength;	// Z

	//  center => Point�̒P�ʃx�N�g���ƁAfront�x�N�g���̓���(cos��)�����߂�
	dotProduct = normalizedVecX * param.frontVecX + normalizedVecZ * param.frontVecZ;

	// cos�Ƃ��p�x�ɕύX
	rad = acosf(dotProduct);


	// ���E���� ------------------------------------------
	//  center => Point�̃x�N�g���ƁAfront�x�N�g���̊O��(y�̂�)�����߂�
	crossProductY = centerToPointVecX * param.frontVecZ - centerToPointVecZ * param.frontVecX;
	// crossProductY�����̒l�̎��Arad�𔽓]
	if (crossProductY < 0.f)
	{
		rad *= -1.f;
	}


	// �p�x����x�N�g�������߂�
	newVecX = sinf(rad);
	newVecZ = cosf(rad);


	// Rader�̍��G�͈͂Ɣ��a�̔䗦�����߂�
	rate = param.raderRadius / RADAR_DETECTION_RANGE;


	// �䗦��center => point�̒�������Z�����l���x�N�g���̒����ɂ���
	newVecX *= rate * vecLength;
	newVecZ *= rate * vecLength;


	// Point�\��
	// �c���͏オ�u-�v�Ȃ̂ŁAz�̕�����ϊ�
	DrawCircle(param.uiCenterX + newVecX, param.uiCenterY - newVecZ, RADAR_POINT_RADIUS, RED);

}