//*****************************************************************************
//!	@file	game.h
//!	@brief	ゲーム処理
//!	@note	
//!	@author
//*****************************************************************************
#ifndef _GAME_H_
#define _GAME_H_
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "CDirectXGraphics.h"
#include "input.h"
#include "GameUtil.h"
#include "CSprite2D.h"
<<<<<<< HEAD
<<<<<<< Updated upstream
#include "obb.h"
=======
>>>>>>> dev
=======
<<<<<<< HEAD
#include "obb.h"
=======
>>>>>>> dev
=======
>>>>>>> parent of a2402fe... PhiEngine
>>>>>>> Stashed changes

//-----------------------------------------------------------------------------
//	プロトタイプ宣言
//-----------------------------------------------------------------------------
bool GameInit(HINSTANCE hinst, HWND hwnd, int width, int height, bool fullscreen);
void GameMain();
void GameExit();
void GameSetEvent();
void GameSetEndFlag();
void GameInput();
void GameUpdate();
void GameRender();

//*****************************************************************************
//	End of file.
//*****************************************************************************

#endif