/*
* @file		RadarPoint.h
* @brief	�N���X RadarPoint �̐錾
* @note		
*/
#pragma once
#include <math.h>
#include <DxLib.h>
#include <vector>
#include "..\Enums.h"
#include "..\Colors.h"
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
	RadarPoint(float x, float z, eRadar::PointType type_);
	~RadarPoint();
	void draw(RadarData& param);	// �`�惁�\�b�h�@Radar.cpp�̒��ŌĂяo��
private:
	float posX = 0.f;						// Point�̍��WX
	float posZ = 0.f;						// Point�̍��WZ

	eRadar::PointType pointType;			// ���
};

