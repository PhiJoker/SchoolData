//*****************************************************************************
//!	@file			main.cpp
//!	@brief			DirectX
//!	@note			2018-5-14
//!	@author			�d�C��			
//*****************************************************************************
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "game.h"

//-----------------------------------------------------------------------------
//	�����N���C�u�����̐ݒ�
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//	�}�N����`
//-----------------------------------------------------------------------------
#define		CLASS_NAME		L"�T���v��"				//	�E�C���h�E�N���X�̖��O
#define		WINDOW_NAME		L"DirectX"				//	�E�C���h�E�̖��O
#define		FULLSCREEN		0						// �t���X�N���[���t���O

//-----------------------------------------------------------------------------
//	�\���̒�`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void	CALLBACK TimerProc(UINT, UINT, DWORD, DWORD, DWORD);


//-----------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-----------------------------------------------------------------------------
int				g_timerid = 0;		// �^�C�}�h�c

//=============================================================================
//!	@fn		WinMain
//!	@brief	�G���g���|�C���g
//!	@param	�C���X�^���X�n���h��
//!	@param	�Ӗ��Ȃ�
//!	@param	�N�����̈���������
//!	@param	�E�C���h�E�\�����[�h
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//!	@note	
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int				width = SCREEN_WIDTH;			// �E�C���h�E�̕� �v�Z�p���[�N
	int				height = SCREEN_HEIGHT;			// �E�C���h�E�̍��� �v�Z�p���[�N


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//	WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,							//	�\������E�C���h�E�̃X�^�C�����w��
		WndProc,							//	�E�C���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,									//	�ʏ�͎g�p���Ȃ��̂Łg0�h���w��
		0,									//	�ʏ�͎g�p���Ȃ��̂Łg0�h���w��
		hInstance,							//	WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
		NULL,								//	�g�p����A�C�R�����w��(Windows�������Ă���A�C�R�����g���Ȃ�NULL)
		LoadCursor(NULL,IDC_ARROW),			//	�}�E�X�J�[�\�����w��
		(HBRUSH)GetStockObject(BLACK_BRUSH),//	�E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
		NULL,								//	Windows�ɂ��郁�j���[��ݒ�
		CLASS_NAME,							//	�E�C���h�E�N���X�̖��O
		NULL								//	�������A�C�R����ݒ肳�ꂽ�ꍇ�̏����L�q
	};
	HWND hWnd;
	MSG msg;

	//	�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT	rWindow, rClient;
	//	�E�C���h�E���쐬
	hWnd = CreateWindowEx(0,				//	�g���E�C���h�E�X�^�C��
		CLASS_NAME,							//	�E�C���h�E�N���X�̖��O
		WINDOW_NAME,						//	�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				//	�E�C���h�E�X�^�C��
		CW_USEDEFAULT,						//	�E�C���h�E�̍���X���W
		CW_USEDEFAULT,						//	�E�C���h�E�̍���Y���W
		SCREEN_WIDTH ,						//	�E�C���h�E�̕�
		SCREEN_HEIGHT ,						//	�E�C���h�E�̍���
		NULL,								//	�e�E�C���h�E�̃n���h��
		NULL,								//	���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,							//	�C���X�^���X�n���h��
		NULL);								//	�E�C���h�E�쐬�f�[�^
											// �E�C���h�E�T�C�Y���Čv�Z�iMetrics�����ł́A�t���[���f�U�C���ŃN���C�A���g�̈�T�C�Y���ς���Ă��܂��̂Łj
	GetWindowRect(hWnd, &rWindow);
	GetClientRect(hWnd, &rClient);
	//width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + SCREEN_WIDTH;
	//height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + SCREEN_HEIGHT;
	SetWindowPos(
		hWnd,
		NULL,
		GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
		width - 1,
		height - 1,
		SWP_NOZORDER);

	//	�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);				//	�w�肳�ꂽ�E�C���h�E�̕\����Ԃ�ݒ�(�E�C���h�E��\��)
	UpdateWindow(hWnd);						//	�E�C���h�E�̏�Ԃ𒼂��ɔ��f(�E�C���h�E�̃N���C�A���g�̈���X�V)
	
	// �Q�[���̏�������
	if (!GameInit(hInstance, hWnd, width, height, FULLSCREEN)) {
		GameExit();
		MessageBox(hWnd, L"ERROR!", L"GameInit Error", MB_OK);
		return false;
	}
	
	timeBeginPeriod(1);						//	����\��ݒ�
	g_timerid = timeSetEvent(16, 1, TimerProc, 1, TIME_PERIODIC);



	//	���b�Z�[�W���[�v
	while (1)	
	{	
		//	���b�Z�[�W���擾�����ꍇ�g0�h��Ԃ�
		//	Windows�̏���
		if (!GetMessage(&msg, NULL, 0, 0))
		{
			//	PostQuitMessage()���Ă΂�āAWM_QUIT���b�Z�[�W�������烋�[�v�I��
			break;
		}
		else
		{
			//	���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&msg);				//	���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
			DispatchMessage(&msg);				//	�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
		}
		
	}
	// �Q�[���I���t���O���Z�b�g����
	GameSetEndFlag();

	if (g_timerid) timeKillEvent(g_timerid);	// �}���`���f�B�A�^�C�}�̏I��
	timeEndPeriod(1);

	GameExit();
	//	�E�C���h�E�N���X�̓o�^���J��
	//	��1�����F�N���X��
	//	��2�����F�A�v���P�[�V�����C���X�^���X�̃n���h��
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//	�I������


	return (int)msg.wParam;
}


//=============================================================================
//!	@fn		WindowProc
//!	@brief	�E�C���h�E�v���V�[�W��
//!	@param	�E�C���h�E�n���h��
//!	@param	���b�Z�[�W
//!	@param	W�p�����[�^
//!	@param	L�p�����[�^
//!	@retval	�I����
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
	{
		nID = MessageBox(NULL, L"�I�����܂����H", L"�m�F", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}
	case WM_DESTROY:						//	�E�C���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);					//	�gWM_QUIT�h���b�Z�[�W��Ԃ�
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//	�K��̏������
}

//=============================================================================
//!	@fn		TimerProc
//!	@brief	�P�U�������ɃC�x���g�I�u�W�F�N�g���Z�b�g����
//!	@param	�^�C�}�h�c
//!	@param	���g�p
//!	@param	���g�p
//!	@param	���g�p
//!	@param	���g�p
//!	@retval	�Ȃ�
//=============================================================================
void CALLBACK TimerProc(UINT, UINT, DWORD, DWORD, DWORD)
{
	GameSetEvent();			// �C�x���g�I�u�W�F�N�g���Z�b�g����
}

//*****************************************************************************
//	End of file.
//*****************************************************************************