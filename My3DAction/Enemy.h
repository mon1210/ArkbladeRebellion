/*
* @file	 Enemy.h
* @brief
*
*
*/
#pragma once
#include "DxLib.h"

//--- ヘッダガードを使用して二度インクルードするのを防ぐ
#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class Stage;

class Enemy : public IGameObject
{
public:
	Enemy(Stage* pParent);
	~Enemy();
	virtual bool move() override;
	virtual void draw(ID3D11DeviceContext* pDeviceContext) override;
	virtual void Init();
	virtual void Update();
	virtual void SetAnim();
protected:
	Stage*	Parent;
	int		anim_handle;
	int		anim_no;
	float	anim_time;
	float	anim_timer;
	float	angle;
	float	hitPoint;
	VECTOR	position;

private:

};