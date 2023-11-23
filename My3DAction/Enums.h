/*
* @file	 Enums.h
* @brief
*
*
*/
#pragma once

// クラス名と被るためプレフィクス付与
namespace ePlayer
{
	enum AnimationNum
	{
		Default = -1,
		Drinking = 0,
		Dying,
		Roll,
		Run,
		Idle

	};
}


// クラス名と被るためプレフィクス付与
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

