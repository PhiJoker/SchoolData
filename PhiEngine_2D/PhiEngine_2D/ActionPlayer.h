//*****************************************************************************
//!	@file	ActionPlayer.cpp
//!	@brief	�A�N�V�����V�[���̃v���C���[����
//!	@note	
//!	@author	�d�C��	2018-07-30
//*****************************************************************************
#pragma once
#ifndef _ACTIONPLAYER_H_
#define _ACTIONPLAYER_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "CSprite2D.h"

class ActionPlayer
{
public:
	CSprite2D mActionPlayer;
	int mlayer;
private:
	bool isUpKey;
	bool isDownKey;
public:
	ActionPlayer() {}
	~ActionPlayer() {}

	void Init(LPDIRECT3DDEVICE9 lpdev);
	void Update(LPDIRECT3DDEVICE9 lpdev);
	void Exit();
};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif
