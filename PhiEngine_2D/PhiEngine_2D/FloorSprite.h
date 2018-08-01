//*****************************************************************************
//!	@file	FloorSprite.cpp
//!	@brief	FloorèàóùÉNÉâÉX
//!	@note	
//!	@author	údäCü∑	2018-07-30
//*****************************************************************************
#pragma once
#ifndef _FLOORSPRITE_H_
#define _FLOORSPRITE_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	"CSprite2D.h"
//#include	"MathUtil.h"

typedef enum {
	FloorType_Plane,//
	FloorType_Ramp,	//	åXéŒñ 
	FloorType_Move,
} FloorType;

class FloorSprite
{
public:
	CSprite2D mFloor;
	FloorType mType;
public:
	FloorSprite() {}
	~FloorSprite() {}

	void Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3 pos, int w, int h, D3DXVECTOR3 boxPos, int boxW, int boxH, FloorType t);
	void Update(LPDIRECT3DDEVICE9 lpdev);
	void Exit();
};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif