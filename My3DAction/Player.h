/*
* @file		Player.h
* @brief	クラス Player の宣言
* @note		当たり判定 () x ()
*/
#pragma once
#include "DxLib.h"
#include "Enums.h"

//--- ヘッダガードを使用して二度インクルードするのを防ぐ
#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class Stage;
class Camera;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	virtual bool move() override;
	virtual void draw() override;
	virtual void SetMove();
	virtual void SetAnim(ePlayer::AnimationNum num);
protected:
	Camera* pCamera;
	VECTOR	position;
	VECTOR  moveVec;
	int		anim_handle;
	int		anim_no;
	int		keyInput;
	float	anim_time;
	float	anim_timer;
	float	angle;
	float	hitPoint;
	bool	moveFlag;
	bool	rollFlag;

private:

};
