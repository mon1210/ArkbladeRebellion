/**
* @file IGameObject.h
* @brief ゲーム上のオブジェクトを表現するクラスを汎化したインターフェースの宣言
* @note 日本のゲーム業界ではタスクと呼ぶ場合がある
*/
#pragma once
#define __IGAMEOBJECT_H__

typedef struct {
	float x;	//	起点
	float y;	//	起点
	float z;	//	起点
	float vx;	//	x成分
	float vy;	//	y成分
	float vz;	//	z成分
}	STEP_VECTOR;


class IGameObject
{
public:
	virtual ~IGameObject() = 0;
	virtual bool move() = 0;
	virtual void draw() = 0;
	//virtual int damage(float amount) = 0;

	STEP_VECTOR step;
	float	Damage;
};

//  マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }
