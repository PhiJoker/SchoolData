//*****************************************************************************
//!	@file			main.cpp
//!	@brief			DirectX
//!	@note			2018-5-14
//!	@author			彭海濤			
//*****************************************************************************
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "game.h"

//-----------------------------------------------------------------------------
//	リンクライブラリの設定
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//	マクロ定義
//-----------------------------------------------------------------------------
#define		CLASS_NAME		L"サンプル"				//	ウインドウクラスの名前
#define		WINDOW_NAME		L"DirectX"				//	ウインドウの名前
#define		FULLSCREEN		0						// フルスクリーンフラグ

//-----------------------------------------------------------------------------
//	構造体定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	プロトタイプ宣言
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void	CALLBACK TimerProc(UINT, UINT, DWORD, DWORD, DWORD);


//-----------------------------------------------------------------------------
//	グローバル変数
//-----------------------------------------------------------------------------
int				g_timerid = 0;		// タイマＩＤ

//=============================================================================
//!	@fn		WinMain
//!	@brief	エントリポイント
//!	@param	インスタンスハンドル
//!	@param	意味なし
//!	@param	起動時の引数文字列
//!	@param	ウインドウ表示モード
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//!	@note	
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int				width = SCREEN_WIDTH;			// ウインドウの幅 計算用ワーク
	int				height = SCREEN_HEIGHT;			// ウインドウの高さ 計算用ワーク


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//	WNDCLASSEXのメモリサイズを指定
		CS_CLASSDC,							//	表示するウインドウのスタイルを指定
		WndProc,							//	ウインドウプロシージャのアドレス(関数名)を指定
		0,									//	通常は使用しないので“0”を指定
		0,									//	通常は使用しないので“0”を指定
		hInstance,							//	WinMainのパラメータのインスタンスハンドルを設定
		NULL,								//	使用するアイコンを指定(Windowsがもっているアイコンを使うならNULL)
		LoadCursor(NULL,IDC_ARROW),			//	マウスカーソルを指定
		(HBRUSH)GetStockObject(BLACK_BRUSH),//	ウインドウのクライアント領域の背景色を設定
		NULL,								//	Windowsにつけるメニューを設定
		CLASS_NAME,							//	ウインドウクラスの名前
		NULL								//	小さいアイコンを設定された場合の情報を記述
	};
	HWND hWnd;
	MSG msg;

	//	ウインドウクラスの登録
	RegisterClassEx(&wcex);

	RECT	rWindow, rClient;
	//	ウインドウを作成
	hWnd = CreateWindowEx(0,				//	拡張ウインドウスタイル
		CLASS_NAME,							//	ウインドウクラスの名前
		WINDOW_NAME,						//	ウインドウの名前
		WS_OVERLAPPEDWINDOW,				//	ウインドウスタイル
		CW_USEDEFAULT,						//	ウインドウの左上X座標
		CW_USEDEFAULT,						//	ウインドウの左上Y座標
		SCREEN_WIDTH ,						//	ウインドウの幅
		SCREEN_HEIGHT ,						//	ウインドウの高さ
		NULL,								//	親ウインドウのハンドル
		NULL,								//	メニューハンドルまたは子ウインドウID
		hInstance,							//	インスタンスハンドル
		NULL);								//	ウインドウ作成データ
											// ウインドウサイズを再計算（Metricsだけでは、フレームデザインでクライアント領域サイズが変わってしまうので）
	GetWindowRect(hWnd, &rWindow);
	GetClientRect(hWnd, &rClient);
	width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + SCREEN_WIDTH;
	height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + SCREEN_HEIGHT;
	SetWindowPos(
		hWnd,
		NULL,
		GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
		width - 1,
		height - 1,
		SWP_NOZORDER);

	//	ウインドウの表示
	ShowWindow(hWnd, nCmdShow);				//	指定されたウインドウの表示状態を設定(ウインドウを表示)
	UpdateWindow(hWnd);						//	ウインドウの状態を直ちに反映(ウインドウのクライアント領域を更新)
	
	// ゲームの初期処理
	if (!GameInit(hInstance, hWnd, width, height, FULLSCREEN)) {
		GameExit();
		MessageBox(hWnd, L"ERROR!", L"GameInit Error", MB_OK);
		return false;
	}
	
	timeBeginPeriod(1);						//	分解能を設定
	g_timerid = timeSetEvent(16, 1, TimerProc, 1, TIME_PERIODIC);



	//	メッセージループ
	while (1)	
	{	
		//	メッセージを取得した場合“0”を返す
		//	Windowsの処理
		if (!GetMessage(&msg, NULL, 0, 0))
		{
			//	PostQuitMessage()が呼ばれて、WM_QUITメッセージが来たらループ終了
			break;
		}
		else
		{
			//	メッセージの翻訳と送出
			TranslateMessage(&msg);				//	仮想キーメッセージを文字メッセージへ変換
			DispatchMessage(&msg);				//	ウインドウプロシージャへメッセージを送出
		}
		
	}
	// ゲーム終了フラグをセットする
	GameSetEndFlag();

	if (g_timerid) timeKillEvent(g_timerid);	// マルチメディアタイマの終了
	timeEndPeriod(1);

	GameExit();
	//	ウインドウクラスの登録を開除
	//	第1引数：クラス名
	//	第2引数：アプリケーションインスタンスのハンドル
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//	終了処理


	return (int)msg.wParam;
}


//=============================================================================
//!	@fn		WindowProc
//!	@brief	ウインドウプロシージャ
//!	@param	ウインドウハンドル
//!	@param	メッセージ
//!	@param	Wパラメータ
//!	@param	Lパラメータ
//!	@retval	終了状況
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
		nID = MessageBox(NULL, L"終了しますか？", L"確認", MB_YESNO);
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
	case WM_DESTROY:						//	ウインドウ破棄のメッセージ
		PostQuitMessage(0);					//	“WM_QUIT”メッセージを返す
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//	規定の処理を提供
}

//=============================================================================
//!	@fn		TimerProc
//!	@brief	１６ｍｓ毎にイベントオブジェクトをセットする
//!	@param	タイマＩＤ
//!	@param	未使用
//!	@param	未使用
//!	@param	未使用
//!	@param	未使用
//!	@retval	なし
//=============================================================================
void CALLBACK TimerProc(UINT, UINT, DWORD, DWORD, DWORD)
{
	GameSetEvent();			// イベントオブジェクトをセットする
}

//*****************************************************************************
//	End of file.
//*****************************************************************************