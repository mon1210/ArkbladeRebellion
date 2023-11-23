/**
* @file IGameScene.h
* @brief �V�[���̊��N���X IGameScene �̐錾
*/
#pragma once
#include <d3d11.h>
/*
*�����w�b�_�t�@�C����������C���N���[�h����邱�Ƃɂ�����h�����߂̃v���v���Z�b�T�e�N�j�b�N
*/
#define __IGAMESCENE_H__

enum GameSceneResultCode;
struct ID3D11DeviceContext;
struct ID2D1RenderTarget;

class IGameScene
{
public:
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode move() = 0;
	//virtual void draw(ID2D1RenderTarget* pRenderTarget) = 0;
	virtual void draw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarge) = 0;
};

