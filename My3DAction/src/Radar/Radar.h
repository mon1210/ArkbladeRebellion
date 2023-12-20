/*
* @file		Radar.h
* @brief	�N���X Radar �̐錾
* @note
*/
#pragma once
#include "..\RadarPoint\RadarPoint.h"

class Radar
{
public:
	Radar();
	~Radar();
	virtual void draw();															// �`�惁�\�b�h
	virtual void addPoint(float x, float z, eRadar::PointType type);				// Point��ǉ����郁�\�b�h
	virtual void addCenter(float x, float z, float front_vec_x, float front_vec_z);	// Radar�̒��S���̂�ݒ肷�郁�\�b�h
	virtual void listReset();														// Point��List�����������郁�\�b�h	���t���[���ŏ��ɌĂяo��
protected:
	float	uiPosX = 120.f;				// UI�̒��S���WX
	float	uiPosY = 120.f;				// UI�̒��S���WY
	float	centerX = 0.f;				// Radar�̒��S���WX
	float	centerZ = 0.f;				// Radar�̒��S���WZ
	float	frontVecX = 0.f;			// ���ʃx�N�g��X
	float	frontVecZ = 0.f;			// ���ʃx�N�g��Z
	float	radius = 100.0f;			// Radar�̔��a 
	std::vector<RadarPoint> pointList;	// Point���X�g�쐬
};

#define WHITE GetColor(255, 255, 255)
#define BLACK GetColor(0, 0, 0)