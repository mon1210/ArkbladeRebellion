/*
* @file		Enums.h
* @brief	eunm�ϐ��錾�p�w�b�_�t�@�C��
* @note		�N���X���Ɣ�邽��namespace�ɂ̓v���t�B�N�X�t�^
*			3D���f���̃A�j���[�V�����ԍ��Ǘ�
*/
#pragma once


namespace ePlayer
{
	enum AnimationNum
	{
		Default = -1,
		Idle = 1,
		Run,
		Roll,
		Drinking,
		Dying = 11

	};
}

namespace eEnemy
{
	enum AnimationNum
	{
		Default = -1,
		Idle = 1,
		Run,
		Swiping,
		Damage,
		Dying
	};
}


enum EnemyState
{
	Default = -1,
	Wait,
	Move, 
	Chase,
	Attack,
	Damage,
	Death,

};


namespace eRadar
{
	enum PointType
	{
		Default = -1,	// -1����p
		Enemy,
	};
}
