/*
* @file		RadarPoint.h
* @brief	�N���X RadarPoint �̐錾
* @note		
*/
#pragma once
#include <math.h>
#include <DxLib.h>
#include <vector>
#include "Enums.h"
#include "Constants.h"


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
	virtual void Draw(RadarData& param);	// �`�惁�\�b�h�@Radar.cpp�̒��ŌĂяo��
private:	// Radar�Ŏg�p�ł��Ȃ��悤��
	float posX;	// Point�̍��W
	float posZ;
	float centerToPointVecX;	// center => point �̃x�N�g��X
	float centerToPointVecZ;	// center => point �̃x�N�g��Z
	float vecLength;			// �x�N�g���̒���
	float normalizedVecX;		// ���K����x�N�g��X
	float normalizedVecZ;		// ���K����x�N�g��Z
	float rad;					// �ʓx�@(radian)�̓x��
	float dotProduct;			// �x�N�g���̓���
	float crossProductY;		// �x�N�g���̊O��
	float newVecX;				// �p�x�����߂���̃x�N�g��X
	float newVecZ;				// �p�x�����߂���̃x�N�g��Z
	float rate;					// Rader�̍��G�͈͂Ɣ��a�̔䗦

	eRadar::PointType pointType;
};

#define RED	GetColor(255, 0, 0)