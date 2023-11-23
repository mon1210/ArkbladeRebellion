#pragma once

#ifndef __IGAMEOBJECT_H__
//ゲーム上のオブジェクトを表現するクラスを汎化したインターフェースの宣言
#include "IGameObject.h"
#endif

struct ID2D1Bitmap;
struct ID2D1RenderTarget;

class BG
{
public:
	BG(ID2D1RenderTarget* pRenderTarget);
	virtual ~BG();
	virtual void draw(ID2D1RenderTarget* pRenderTarget);
	//virtual int setX(float x);
	//virtual int getX();
	//virtual float getMapWidth();
	//virtual float getMapHight();
	//virtual int tile_code(float x, float y);
	//virtual int mapdata_decode(int index);
	//virtual void getStepVector(float x, float y, STEP_VECTOR* step);
	//virtual void resetMapData(int num);
protected:
	//int mMapW, mMapH;	//	mapのwidthとheight
	//int mChipW, mChipH;	//	map-chipのwidthとheight
	//int mPitch;			//	map-chip データの行ピッチ
	//int m_iX;			//	現在プレイヤーがいるx座標
	//ID2D1Bitmap* m_pMapChip;
	ID2D1Bitmap* BGImage;
	//MAPDATA	map;
};
