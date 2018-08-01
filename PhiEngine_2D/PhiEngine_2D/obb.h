//*****************************************************************************
//!	@file	obb.h
//!	@brief	OBBëŒOBBÇÃè’ìÀîªíË (2D)
//!	@note	
//!	@author	2018/07/13
//*****************************************************************************
#ifndef _OBB_H_
#define _OBB_H_
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "CSprite2D.h"

typedef struct tagOBB
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 dir[2];
	float		len[2];
}OBB;

void CreateOBB(OBB* pOutObb, const D3DXVECTOR2 &pos, const D3DXMATRIX &rotateMtx, const D3DXVECTOR2 &len);
float LenSegOnSeparateAxis(D3DXVECTOR2* sep, D3DXVECTOR2* e1, D3DXVECTOR2*e2);

bool ObbVSObb2D(const OBB &obb1, const OBB &obb2);
//	ìñÇΩÇËîªíËÅi2DÇÃOBBvsOBBÅj
bool Collision2D( CSprite2D &obj1,  CSprite2D &obj2);
//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif