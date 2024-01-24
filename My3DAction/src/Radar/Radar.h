/*
* @file		Radar.h
* @brief	�N���X Radar �̐錾
*/
#pragma once
#include "..\RadarPoint\RadarPoint.h"

class Radar
{
public:
	/**
	* @brief Radar�̃R���X�g���N�^
	*/
	Radar();

	// �f�X�g���N�^
	~Radar();

	/**
	* @brief �`�惁�\�b�h
	*/
	void draw();

	/**
	* @brief Point��ǉ����郁�\�b�h
	* @note  ���W�擾���K�v�Ȃ̂Ŗ��t���[���Ăяo��
	*		 RadarPoint�̃R���X�g���N�^�Ăяo��
	* @param[in] x�@	x���W
	* @param[in] z�@	z���W
	* @param[in] type_	Point�̎�ށ@����Point�\���Ă��邩
	*/
	void addPoint(float x, float z, eRadar::PointType type);

	/**
	* @brief Radar�̒��S���̂�ݒ肷�郁�\�b�h
	* @note  ���W�擾���K�v�Ȃ̂Ŗ��t���[���Ăяo��
	*		 Player�����S�Ȃ̂�Player�ŌĂяo���Ă���
	* @param[in] x�@			���S���̂�x���W
	* @param[in] z�@			���S���̂�z���W
	* @param[in] front_vec_x	���S���̂̑O���x�N�g��X
	* @param[in] front_vec_z	���S���̂̑O���x�N�g��Z
	*/
	void addCenter(float x, float z, float front_vec_x, float front_vec_z);

	/**
	* @brief Point��List�����������郁�\�b�h
	* @note  ���t���[���ŏ��ɌĂяo��
	*/
	void listReset();
private:
	float	uiPosX = 120.f;				// UI�̒��S���WX
	float	uiPosY = 120.f;				// UI�̒��S���WY
	float	centerX = 0.f;				// Radar�̒��S���WX
	float	centerZ = 0.f;				// Radar�̒��S���WZ
	float	frontVecX = 0.f;			// ���ʃx�N�g��X
	float	frontVecZ = 0.f;			// ���ʃx�N�g��Z
	float	radius = 100.0f;			// Radar�̔��a 

	std::vector<RadarPoint> pointList;	// Point���X�g�쐬
};