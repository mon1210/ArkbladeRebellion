#pragma once

#ifndef __IGAMEOBJECT_H__
//�Q�[����̃I�u�W�F�N�g��\������N���X��ĉ������C���^�[�t�F�[�X�̐錾
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
	//int mMapW, mMapH;	//	map��width��height
	//int mChipW, mChipH;	//	map-chip��width��height
	//int mPitch;			//	map-chip �f�[�^�̍s�s�b�`
	//int m_iX;			//	���݃v���C���[������x���W
	//ID2D1Bitmap* m_pMapChip;
	ID2D1Bitmap* BGImage;
	//MAPDATA	map;
};
