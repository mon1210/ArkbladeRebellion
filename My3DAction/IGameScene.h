/**
* @file IGameScene.h
* @brief シーンの基底クラス IGameScene の宣言
*/
#pragma once
#include <d3d11.h>
/*
*同じヘッダファイルが複数回インクルードされることによる問題を防ぐためのプリプロセッサテクニック
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

