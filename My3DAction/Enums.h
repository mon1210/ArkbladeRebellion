/*
* @file		Enums.h
* @brief	eunm変数宣言用ヘッダファイル
* @note		クラス名と被るためnamespaceにはプレフィクス付与
*			3Dモデルのアニメーション番号管理
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
		Default = -1,	// -1代入用
		Enemy,
	};
}
