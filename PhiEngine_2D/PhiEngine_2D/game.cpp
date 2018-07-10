//*****************************************************************************
//!	@file	game.cpp
//!	@brief	
//!	@note	ゲーム処理
//!	@author	
//*****************************************************************************
#include "game.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
CDirectXGraphics	*g_DXGrobj = nullptr;		// DirectX Graphicsオブジェクト

D3DXMATRIX			g_MatView;			// カメラ行列
D3DXMATRIX			g_MatProjection;	// プロジェクション変換行列
D3DXMATRIX			g_MatWorld;			// ワールド変換行列

HANDLE				g_hEventHandle;		// イベントハンドル
bool				g_EndFlag = false;	// 終了フラグ
std::thread			g_gamemainthread;	// ゲームメインスレッド

SceneType			g_SceneStage;
LPDIRECT3DTEXTURE9* g_pTex1;
LPDIRECT3DTEXTURE9* g_pTex2;
LPDIRECT3DTEXTURE9* g_pTex3;


//==============================================================================
//!	@fn		GameInit
//!	@brief	ゲーム初期処理
//!	@param	インスタンス値
//!	@param	ウインドウハンドル値
//!	@param	ウインドウサイズ幅（補正済みの値）
//!	@param	ウインドウサイズ高さ（補正済みの値）
//!	@param　	フルスクリーンフラグ　true ; フルスクリーン　false : ウインドウ
//!	@retval	true 成功　false 失敗
//==============================================================================
bool GameInit(HINSTANCE hinst, HWND hwnd, int width, int height, bool fullscreen)
{
	bool sts;
	g_DXGrobj = new CDirectXGraphics();	// DirectX Graphicsオブジェクト生成
	sts = g_DXGrobj->Init(hwnd, fullscreen, width, height);	// DirectX Graphicsオブジェクト初期化

	if (!sts) {
		MessageBox(hwnd, L"ERROR!!", L"DirectX 初期化エラー", MB_OK);
		return false;
	}

	// カメラ変換行列作成
	D3DXMatrixLookAtLH(&g_MatView,
		&D3DXVECTOR3(0.0f, 0.0f, -10.0f),		// 視点
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 注視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// 上向き

												// カメラ行列を固定パイプラインへセット
	g_DXGrobj->GetDXDevice()->SetTransform(D3DTS_VIEW, &g_MatView);

	// プロジェクション変換行列作成
	D3DXMatrixPerspectiveFovLH(&g_MatProjection,
		D3DX_PI / 2,					// 視野角
		(float)width / (float)height,	// アスペクト比
		1.0f,						// ニアプレーン
		1000.0f);					// ファープレーン

	// 射影変換行列を固定パイプラインへセット
	g_DXGrobj->GetDXDevice()->SetTransform(D3DTS_PROJECTION, &g_MatProjection);
	// Ｚバッファ有効
	g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ライト有効
	g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_LIGHTING, false);

	//アルファブレンディングを設定する
	g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャステージステート
	g_DXGrobj->GetDXDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_DXGrobj->GetDXDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_DXGrobj->GetDXDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// DirectT Input初期化
	InitInput(hinst, hwnd);

	// イベントハンドル生成
	g_hEventHandle = CreateEvent(NULL, false, false, NULL);
	if (g_hEventHandle == NULL) {
		MessageBox(hwnd, L"ERROR!!", L"CreateEvent エラー", MB_OK);
		return false;
	}

	// スレッド生成(ゲームメイン)
	g_gamemainthread = std::thread(GameMain);

	//g_GameState = SceneTitle;
	g_SceneStage = SceneTitle;

	g_pTex1 = LoadTexture(g_DXGrobj->GetDXDevice(),L"title.png", g_pTex1);

	return	true;
}

//==============================================================================
//!	@fn		GameInput
//!	@brief	ゲーム入力検知処理
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameInput() {
	UpdateInput();				// 入力を検知する

	static float posX = 0.0f;
	static float posY = 0.0f;
	static float angle = 0.0f;
	static float sX = 1.0f;
	static float sY = 1.0f;
	if (GetKeyboardPress(DIK_LEFT)) {
		posX -= 0.1f;
	}
	if (GetKeyboardPress(DIK_RIGHT)) {
		posX += 0.1f;
	}
	if (GetKeyboardPress(DIK_UP)) {
		posY += 0.1f;
	}
	if (GetKeyboardPress(DIK_DOWN)) {
		posY -= 0.1f;
	}
	if (GetKeyboardPress(DIK_Z)) {
		angle -= 0.01f;
	}
	if (GetKeyboardPress(DIK_X)) {
		angle += 0.01f;
	}
	if(GetKeyboardPress(DIK_C)) {
		sX += 0.1f;
		sY += 0.1f;
	}
	if (GetKeyboardPress(DIK_V)) {
		sX -= 0.1f;
		sY -= 0.1f;
		if (sX<1.0f)
		{
			sX = 1.0f;
			sY = 1.0f;
		}
	}
	MovePolygon(posX, posY,angle,sX,sY);
}

//==============================================================================
//!	@fn		GameUpdate
//!	@brief	ゲーム更新処理
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameUpdate() {
	
}

//==============================================================================
//!	@fn		GameRender
//!	@brief	ゲーム更新処理
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameRender() {
	HRESULT  hr;
	RECT formatRect;
	formatRect.left = SCREEN_WIDTH / 2.0 - 80;
	formatRect.top = 0;
	// ターゲットバッファのクリア、Ｚバッファのクリア
	g_DXGrobj->GetDXDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// 描画の開始をＤＩＲＥＣＴＸに通知
	g_DXGrobj->GetDXDevice()->BeginScene();

	switch (g_SceneStage)
	{
	case SceneTitle:
	{
		Draw2dPolygon(g_DXGrobj->GetDXDevice(), g_pTex1);
		break;
	}
	case SceneRun:
	{
		break;
	}
	case SceneEnd:
	{
		break;
	}
	default:
		break;
	}

	Draw2dPolygon(g_DXGrobj->GetDXDevice(), g_pTex1);
	//DrawTriangle(g_DXGrobj->GetDXDevice(), g_pTex1);
	g_DXGrobj->GetDXDevice()->EndScene();	// 描画の終了を待つ


	hr = g_DXGrobj->GetDXDevice()->Present(NULL, NULL, NULL, NULL);	// バックバッファからプライマリバッファへ転送
	if (hr != D3D_OK) {
		g_DXGrobj->GetDXDevice()->Reset(&g_DXGrobj->GetDXD3dpp());
	}
}

//==============================================================================
//!	@fn		GameMain
//!	@brief	ゲームループ処理
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameMain()
{
	while (1) {
		DWORD sts = WaitForSingleObject(g_hEventHandle, 1000);	// イベントフラグがセットされるのを待つ（1000msでタイムアウト）
		if (sts == WAIT_FAILED) {
			break;
		}
		else if (sts == WAIT_TIMEOUT) {
			if (g_EndFlag) {
				break;
			}
			continue;
		}

		GameInput();					// 入力
		GameUpdate();					// 更新
		GameRender();					// 描画
	}
}

//==============================================================================
//!	@fn		GameExit
//!	@brief	ゲーム終了処理
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameExit()
{
	ReleaseTexture(g_pTex1);
	ReleaseTexture(g_pTex2);
	ReleaseTexture(g_pTex3);

	g_gamemainthread.join();					// ゲームメインスレッドの終了を待つ

	CloseHandle(g_hEventHandle);				// イベントハンドルクローズ

	if (g_DXGrobj != nullptr) {
		g_DXGrobj->Exit();						// DirectXのグラフィックオブジェクトの終了処理
		delete g_DXGrobj;
		g_DXGrobj = nullptr;
	}

	// DirectT Input終了処理
	UninitInput();
}

//==============================================================================
//!	@fn		GameSetEvent
//!	@brief	ゲームループ内のイベントオブジェクトをセットする
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameSetEvent() {
	if (!g_EndFlag) {
		SetEvent(g_hEventHandle);	// 終了フラグがセットされていなければイベントをセットする
	}
}

//==============================================================================
//!	@fn		GameSetEndFlag
//!	@brief	ゲームループの終了フラグをセットする
//!	@param　	
//!	@retval	なし
//==============================================================================
void GameSetEndFlag() {
	g_EndFlag = true;				// 終了フラグをオンにする
}

//******************************************************************************
//	End of file.
//******************************************************************************
