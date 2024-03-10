/**
* @file		RadarPoint.h
* @brief	�N���X RadarPoint �̐錾
*/
#pragma once
#include <math.h>
#include <DxLib.h>
#include <vector>
#include "..\Enums.h"
#include "..\Constants.h"


// Radar�N���X�Œ��g����A���̃N���X�Ŏg�p
struct RadarData
{
	//! UI�̒��S���WX
	float uiCenterX;
	//! UI�̒��S���WY
	float uiCenterY;

	//! Radar�̒��S���WX
	float centerX;
	//! Radar�̒��S���WZ
	float centerZ;

	//! ���ʃx�N�g��X
	float frontVecX;
	//! ���ʃx�N�g��Z
	float frontVecZ;

	//! Radar�̔��a
	int raderRadius;
};


class RadarPoint
{
public:
	/**
	* @brief RadarPoint�̃R���X�g���N�^
	* @note  posX, posZ, pointType�͈����ŏ������A�Ăяo�����ɒl����������
	* @param[in] x�@	x���W
	* @param[in] z�@	z���W
	* @param[in] type_	Point�̎�ށ@����Point�\���Ă��邩
	*/
	RadarPoint(float x, float z, eRadar::PointType type);

	/**
	* @brief RadarPoint�̃f�X�g���N�^
	*/
	~RadarPoint();

	/**
	* @brief �`�惁�\�b�h
	* @note  Radar�ŌĂяo��
	* @param[in] param�@Radar�̃p�����[�^��ۑ������\����
	*/
	void draw(RadarData& param);
private:
	//! Point�̍��WX
	float posX = 0.f;
	//! Point�̍��WZ
	float posZ = 0.f;

	//! ���
	eRadar::PointType pointType = eRadar::PointType::Default;
};

