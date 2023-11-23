/**
* @file Selector.h
* @brief �N���XCSelector�̐錾�t�@�C��
*/
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"
// 
#include "Player.h"
// 
#include "Model.h"

//--- �w�b�_�K�[�h�ŁA�����w�b�_�t�@�C����������C���N���[�h����邱�Ƃɂ�����h���ł���
#ifndef __IGAMESCENE_H__
#include "IGameScene.h"
#endif

enum eGamePhase {
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200
};

enum GameSceneResultCode {
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

class IGameScene;	// �V�[���Ǘ��N���X
class Player;
class Model;
struct ID3D11Device;
struct ID3D11DeviceContext;
//struct ID2D1RenderTarget;
struct IDWriteTextFormat;
//struct ID2D1SolidColorBrush;

class Selector
{
public:
	Selector(ID3D11RenderTargetView* pRenderTargetView);
	virtual ~Selector(void);
	void doAnim();		//	�Q�[���S�̂̃A�j���[�g
	void doDraw(ID3D11RenderTargetView* pRenderTargetView, ID2D1RenderTarget* pRenderTarget);	//	�Q�[���S�̂̕`��
	ID3D11RenderTargetView* GetRenderTarget();
	ID2D1RenderTarget* GetRenderTarget2D();
	IDWriteTextFormat* GetTextFormat();
protected:
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
	ID3D11RenderTargetView* RenderTargetView;
	ID2D1RenderTarget* RenderTarge;
	IDWriteTextFormat* TextFormat;
	//ID2D1SolidColorBrush* WhiteBrush;

	Player* pPlayer;

	IGameScene* pScene;		//	�V�[��
	eGamePhase eGamePhase;	//	��ԕϐ�

	//INT m_iWait;
	INT		count;	//	�J�E���^�[(�f�o�b�O�p)
};

//	�}�N����`
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY if(o){ delete [] (o); o = NULL; }

