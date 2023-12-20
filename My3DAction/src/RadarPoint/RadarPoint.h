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
	virtual void draw(RadarData& param);	// �`�惁�\�b�h�@Radar.cpp�̒��ŌĂяo��
private:// Radar�Ŏg�p�ł��Ȃ��悤��
	float posX = 0.f;						// Point�̍��WX
	float posZ = 0.f;						// Point�̍��WZ
	float centerToPointVecX = 0.f;			// center => point �̃x�N�g��X
	float centerToPointVecZ = 0.f;			// center => point �̃x�N�g��Z
	float vecLength = 0.f;					// �x�N�g���̒���
	float normalizedVecX = 0.f;				// ���K����x�N�g��X
	float normalizedVecZ = 0.f;				// ���K����x�N�g��Z
	float rad = 0.f;						// �ʓx�@(radian)�̓x��
	float dotProduct = 0.f;					// �x�N�g���̓���
	float crossProductY = 0.f;				// �x�N�g���̊O��
	float newVecX = 0.f;					// �p�x�����߂���̃x�N�g��X
	float newVecZ = 0.f;					// �p�x�����߂���̃x�N�g��Z
	float rate = 0.f;						// Rader�̍��G�͈͂Ɣ��a�̔䗦

	eRadar::PointType pointType;			// ���
};

#define RED	GetColor(255, 0, 0)