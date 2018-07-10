//======================================================================
//!	@file	GameUtil.h
//!	@brief	Utility
//!	@note	
//!	@author	彭海涛	2018-07-09
//======================================================================
#ifndef _GAMEUTIL_H
#define _GAMEUTIL_H
#pragma once

#include	<Windows.h>
#include	<stdio.h>
#include	<process.h>
#include	<thread>
#include	<crtdbg.h>
#include	<d3d9.h>
#include	<d3dx9.h>
#include	"input.h"

//**********************************************************************
//	リンクライブラリの設定
//**********************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")

//**********************************************************************
//	マクロ定義
//**********************************************************************
#define		SCREEN_WIDTH	640
#define		SCREEN_HEIGHT	480
#define		PI				3.14159265f

//	シーン状態
typedef enum
{
	SceneTitle,		//	タイトル
	SceneMenu,		//	メニュー
	SceneRun,		//	ゲーム
	SceneEnd		//	終了
}SceneType;

//SceneType g_GameState;

#endif