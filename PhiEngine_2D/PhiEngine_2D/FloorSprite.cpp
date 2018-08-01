//*****************************************************************************
//!	@file	FloorSprite.cpp
//!	@brief	FloorèàóùÉNÉâÉX
//!	@note	
//!	@author	údäCü∑	2018-07-30
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "FloorSprite.h"

void FloorSprite::Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3 pos, int w, int h, D3DXVECTOR3 boxPos, int boxW, int boxH, FloorType t)
{
	mFloor.Init(lpdev, filename, pos, w, h, false);
	mFloor.SetBoxPosition(boxPos);
	mFloor.SetBoxCollision(boxW, boxH);
	mType = t;
}

void FloorSprite::Update(LPDIRECT3DDEVICE9 lpdev)
{
	//mFloor.Update(lpdev);
}

void FloorSprite::Exit()
{
	mFloor.Exit();
}

//*****************************************************************************
//	End of file.
//*****************************************************************************