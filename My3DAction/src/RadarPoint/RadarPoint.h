/*
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
	float uiCenterX;	// UI�̒��S���W(XY)
	float uiCenterY;

	float centerX;		// Radar�̒��S���W(XZ)
	float centerZ;

	float frontVecX;	// ���ʃx�N�g��(XZ)
	float frontVecZ;

	float raderRadius;	// Radar�̔��a
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

	// �f�X�g���N�^
	~RadarPoint();

	/**
	* @brief �`�惁�\�b�h
	* @note  Radar�ŌĂяo��
	* @param[in] param�@Radar�̃p�����[�^��ۑ������\����
	*/
	void draw(RadarData& param);
private:
	float posX = 0.f;				// Point�̍��WX
	float posZ = 0.f;				// Point�̍��WZ

	eRadar::PointType pointType;	// ���
};

