//*****************************************************************************
//!	@file	game.h
//!	@brief	�Q�[������
//!	@note	
//!	@author
//*****************************************************************************
#ifndef _GAME_H_
#define _GAME_H_
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <list>
#include "CDirectXGraphics.h"
#include "input.h"
#include "GameUtil.h"
#include "CSprite2D.h"
#include "obb.h"
#include "SceneManager.h"
//-----------------------------------------------------------------------------
//	�v���g�^�C�v�錾
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