/**
* @file		My3DAction.cpp
* @author	R.Monda
* @date		..2023
* @brief	�V�[���Ǘ��N���X		: Selector	(Selector.h)
*			�Q�[���V�[���N���X		: Stage		(Stage.h)
*			�v���C���[�N���X		: Player	(Player.h)
*			�w�i�E�}�b�v�N���X		: BG		(BG.h)
* @note		�G���[���o���ۂ́A�v���W�F�N�g�̃v���p�e�B���J���A
*			C/C++	 -> �S�� -> �ǉ��̃C���N���[�h�f�B���N�g����'Lib;%(AdditionalIncludeDirectories)'��ǉ����� ����
*			�����J�[ -> �S�� -> �ǉ��̃��C�u�����f�B���N�g����'Lib;%(AdditionalIncludeDirectories)'��ǉ����� ����
*			�����J�[ -> ���� -> �ǉ��̈ˑ��t�@�C����'d3d11.lib'��ǉ����Ă�������
*/

// Windows�A�v���P�[�V�����J���p�̋��ʃw�b�_�t�@�C��
#include "stdafx.h"
// CRT �f�o�b�O�w�b�_�t�@�C�����C���N���[�h
#include <crtdbg.h>
// TCHAR �^�C�v��}�N�����`�����w�b�_�t�@�C�����C���N���[�h
#include <tchar.h>
// �W�����o�͊֐���񋟂��� C ���C�u�����w�b�_�t�@�C�����C���N���[�h
#include <stdio.h>
// Direct2D�̃w�b�_�t�@�C�����C���N���[�h
#include <d2d1.h>

#include <d3d11.h>
#include <d2d1_1.h>

// DirectWrite �w�b�_�[�t�@�C�����C���N���[�h
#include <dwrite.h>
// �Q�[���V�[���ƃZ���N�^�[�̊Ǘ��Ɋ֘A����w�b�_�t�@�C��
#include "Selector.h"
// �萔�l���߂��w�b�_�t�@�C��
#include "Constants.h"

#pragma comment(lib,"d2d1.lib")		//	direct2d �ɕK�v
#pragma comment(lib,"dwrite.lib")	//	�����\���ɕK�v

#define MAX_LOADSTRING 100

#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if(o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)	if(o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if(o){ delete [] (o); o = NULL; }


//!	�֐�WndProc�̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//!	�O���[�o���ϐ�
ID2D1Factory* g_pD2DFactory = NULL;		//	D2D1Factory�I�u�W�F�N�g
ID2D1HwndRenderTarget* g_pRenderTarget = NULL;	//	�`��^�[�Q�b�g
ID3D11Device* g_pD3DDevice = NULL;                 // D3D11�f�o�C�X
ID3D11DeviceContext* g_pD3DDeviceContext = NULL;   // D3D11�f�o�C�X�R���e�L�X�g
IDXGISwapChain* g_pSwapChain = NULL;                // �X���b�v�`�F�[��
ID3D11RenderTargetView* g_pRenderTargetView = NULL;// �����_�[�^�[�Q�b�g�r���[


double		g_dblDenominator;
double		g_dblFrame;
__int64		g_i64OldTimer;
#define FPS 60.0
#define INTERVAL (1.0/FPS)

Selector* g_pSelector = NULL;	//	�Q�[���V�X�e���I�u�W�F�N�g

/**
* @fn
* @brief	�A�v���P�[�V�����̃G���g���[�|�C���g
*/
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	   lpCmdLine,
	int	   nCmdShow)
{
	//! �f�o�b�O�p�̃t���O�Z�b�g
	//--- �������f�o�b�O���s�����߂Ɏg�p����� _Crt ���C�u�����̊֐�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//--- COM�iComponent Object Model�j�����������邽�߂̊֐�
	CoInitialize(NULL);		// ��������COM�g�p��

	//! �ϐ��錾
	WNDCLASSEX wcex;	//	�E�B���h�E�N���X�\����
	HWND	hWnd;		//	�E�B���h�E�n���h��
	RECT	bounds, client;	//	RECT�\����


	/*********************
		1.����������
	*********************/

	//	1-a	�E�B���h�E�N���X�̓o�^
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;	//	�E�B���h�E�v���V�[�W���̓o�^
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;				//	�A�v���P�[�V�����C���X�^���X
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + WINDOW_BG_COLOR_OFFSET);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("My3DAction");	//	�E�B���h�E�N���X��
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wcex);


	//	1-b �E�B���h�E�̐���
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wcex.lpszClassName, _T("My3DAction"),
		WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, WINDOW_POS_Y, WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;

	// �E�B���h�E�T�C�Y�̒���
	GetWindowRect(hWnd, &bounds); // �E�B���h�E�T�C�Y	:�g���܂񂾃T�C�Y
	GetClientRect(hWnd, &client); // �N���C�A���g�T�C�Y	:�g���܂܂Ȃ��\���̈�
	MoveWindow(hWnd, bounds.left, bounds.top,
		WINDOW_WIDTH_SIZE * 2 - client.right,		// �E�B���h�E�T�C�Y�ɘg�𑫂�->�N���C�A���g�T�C�Y��_�����T�C�Y�ɂł���
		WINDOW_HEIGHT_SIZE * 2 - client.bottom,
		false);

	// �E�B���h�E�̍ĕ\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//	�ĕ\���̍ہAWndProc���Ăяo����邱�Ƃɒ��ӁI


	//	1-c Direct2D�̏����� ----------------------------------------------------------------
	//{
	//	HRESULT hr;
	//	//	Direct2D Factory �̐���
	//	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	//	GetClientRect(hWnd, &client);
	//	D2D1_SIZE_U size = D2D1::SizeU(
	//		client.right - client.left,
	//		client.bottom - client.top
	//	);

	//	//	Direct2D �`��^�[�Q�b�g �̐���
	//	hr = g_pD2DFactory->CreateHwndRenderTarget(
	//		D2D1::RenderTargetProperties(),
	//		D2D1::HwndRenderTargetProperties(hWnd, size),
	//		&g_pRenderTarget
	//	);
	//}
	

	//	1-c Direct3D�̏�����
	{
		/*
			�u�o�b�t�@�v
			�����̋@���\�t�g�E�F�A�̊ԂŃf�[�^������肷��Ƃ��ɁA
			�������x��]�����x�̍���₤���߂�
			�f�[�^���ꎞ�I�ɕۑ����Ă����L�����u��L���̈�̂���
		*/
		DXGI_SWAP_CHAIN_DESC scd = {};
		scd.BufferCount = 1;									 // �o�b�t�@�̐�
		scd.BufferDesc.Width = WINDOW_WIDTH_SIZE;                // �o�b�t�@�̕�
		scd.BufferDesc.Height = WINDOW_HEIGHT_SIZE;              // �o�b�t�@�̍���
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;      // �o�b�t�@�̃t�H�[�}�b�g
		scd.BufferDesc.RefreshRate.Numerator = 60;               // ���t���b�V�����[�g�̕��q
		scd.BufferDesc.RefreshRate.Denominator = 1;              // ���t���b�V�����[�g�̕���
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;       // �o�b�t�@�̎g�p�@
		scd.OutputWindow = hWnd;								 // �o�͐�̃E�B���h�E�n���h��
		scd.SampleDesc.Count = 1;                                // �}���`�T���v�����O�̃T���v����
		scd.SampleDesc.Quality = 0;                              // �}���`�T���v�����O�̕i��
		scd.Windowed = TRUE;                                     // �E�B���h�E���[�h�ŋN��

		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
		D3D11CreateDeviceAndSwapChain(
			nullptr,                             // �f�o�C�X���쐬����A�_�v�^ (nullptr �Ȃ�΃f�t�H���g�̃A�_�v�^���g�p)
			D3D_DRIVER_TYPE_HARDWARE,            // �h���C�o�[�^�C�v
			nullptr,                             // �\�t�g�E�F�A�����_���[���g�p����ꍇ�̃h���C�o�[���W���[��
			0,                                   // �t���O
			featureLevels,                       // �T�|�[�g����Direct3D�̋@�\���x���̔z��
			_countof(featureLevels),             // �@�\���x���̐�
			D3D11_SDK_VERSION,                   // SDK�̃o�[�W����
			&scd,                                // �X���b�v�`�F�[���̐ݒ�
			&g_pSwapChain,                       // �쐬���ꂽ�X���b�v�`�F�[�����i�[����ϐ��ւ̃|�C���^
			&g_pD3DDevice,                       // �쐬���ꂽ�f�o�C�X���i�[����ϐ��ւ̃|�C���^
			nullptr,                             // �T�|�[�g�����@�\���x�����i�[����ϐ��ւ̃|�C���^
			&g_pD3DDeviceContext                 // �쐬���ꂽ�f�o�C�X�R���e�L�X�g���i�[����ϐ��ւ̃|�C���^
		);
		ID3D11Texture2D* backBuffer = nullptr;
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
		g_pD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &g_pRenderTargetView);
		backBuffer->Release();
	}

	//	1-d �^�C�}�[�̏�����
	::QueryPerformanceCounter((LARGE_INTEGER*)&g_i64OldTimer);
	__int64		i64Tmp;
	::QueryPerformanceFrequency((LARGE_INTEGER*)&i64Tmp);
	g_dblDenominator = DOUBLE_ONE / (double)i64Tmp;
	g_dblFrame = 0.0f;

	//	�Q�[���V�X�e��������
	g_pSelector = new Selector(g_pRenderTargetView);


	/**************************
		2.���b�Z�[�W���[�v
	**************************/
	MSG		msg;
	while (true && !CheckHitKey(KEY_INPUT_ESCAPE)) {

		//// �J�����̕`��ʒu�ƌ���ʒu���w��
        SetCameraPositionAndTargetAndUpVec(
            VGet(0.f, 0.f, 0.f),    // �J�������W
            VGet(0.f, 0.f, 1.f),    // �J�����̌���ʒu
            VGet(0.f, 1.f, 0.f)     // �Œ�
        );
        // �J�����̈ʒu�ƌ�����ݒ�     ��������
        //SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 1200.0f, -2000.0f), VGet(0.0f, 400.0f, 0.0f));

        // �w�i�̐F�ύX�@�D�F
        SetBackgroundColor(128, 128, 128);

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {	// PeekMessage() �C�x���g�̎��o��
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);		//	�V���[�g�J�b�g���̕ϊ�
			DispatchMessage(&msg);		//	�C�x���g�̔z�M�BWndProc() �Ăяo��
		}
		else {

			double	t;
			::QueryPerformanceCounter((LARGE_INTEGER*)&i64Tmp);
			t = (i64Tmp - g_i64OldTimer) * g_dblDenominator;
			g_i64OldTimer = i64Tmp;
			g_dblFrame += t;

			if (g_dblFrame >= INTERVAL) {
				int c = (int)(g_dblFrame / INTERVAL);
				g_dblFrame -= INTERVAL * c;

				if (g_pSelector)
					g_pSelector->doAnim();

				InvalidateRect(hWnd, NULL, false);	//	���������̎��s
			}
		}
	}



	/**************************
			3.�I������
	**************************/

	SAFE_DELETE(g_pSelector);
	SAFE_RELEASE(g_pRenderTarget);
	SAFE_RELEASE(g_pD2DFactory);

	SAFE_RELEASE(g_pRenderTargetView);
	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pD3DDeviceContext);
	SAFE_RELEASE(g_pD3DDevice);

	return (int)msg.wParam;
}


/**
* @fn
* @brief	�E�B���h�E�ɓn���ꂽ�C�x���g�̃n���h��
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message) {

	case WM_PAINT:
		if (g_pRenderTargetView) {

			//g_pRenderTarget->BeginDraw();	//	�`��J�n

			//g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());	// Transform �̐ݒ�

			//g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkBlue));	//	��ʂ̃N���A

			////	���̒��ɕ`�揈��������

			//if (g_pSelector)
			//	g_pSelector->doDraw(g_pRenderTargetView);

			////	���̒��ɕ`�揈��������

			//g_pRenderTarget->EndDraw();		//	�`��I��


			//	���̒��ɕ`�揈��������

			if (g_pSelector)
				g_pSelector->doDraw(g_pRenderTargetView, g_pRenderTarget);

			//	���̒��ɕ`�揈��������

			// �o�b�N�o�b�t�@�̓��e��\��
			g_pSwapChain->Present(0, 0);

		}
		ValidateRect(hWnd, NULL);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}