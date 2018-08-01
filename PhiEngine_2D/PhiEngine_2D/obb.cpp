//*****************************************************************************
//!	@file	obb.h
//!	@brief	OBB‘ÎOBB‚ÌÕ“Ë”»’è
//!	@note	
//!	@author	2018/07/13
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "obb.h"


//*****************************************************************************
//	End of file.
//*****************************************************************************

void CreateOBB(OBB* pOutObb, const D3DXVECTOR2 &pos, const D3DXMATRIX &rotateMtx, const D3DXVECTOR2 &len)
{
	pOutObb->pos.x = pos.x;
	pOutObb->pos.y = pos.y;
	pOutObb->len[0] = len.x;
	pOutObb->len[1] = len.y;
	pOutObb->dir[0] = D3DXVECTOR2(rotateMtx._11, rotateMtx._12);
	pOutObb->dir[1] = D3DXVECTOR2(rotateMtx._21, rotateMtx._22);
}

float LenSegOnSeparateAxis(D3DXVECTOR2 * sep, D3DXVECTOR2 * e1, D3DXVECTOR2 * e2)
{
	float r1 = fabs(D3DXVec2Dot(sep, e1));
	float r2 = fabs(D3DXVec2Dot(sep, e2));
	return r1 + r2;
}

bool ObbVSObb2D(const OBB & obb1, const OBB & obb2)
{
	D3DXVECTOR2 NAe1 = obb1.dir[0], Ae1 = NAe1 *obb1.len[0];
	D3DXVECTOR2 NAe2 = obb1.dir[1], Ae2 = NAe2 *obb1.len[1];

	D3DXVECTOR2 NBe1 = obb2.dir[0], Be1 = NBe1 *obb2.len[0];
	D3DXVECTOR2 NBe2 = obb2.dir[1], Be2 = NBe2 *obb2.len[1];
	D3DXVECTOR2 Interval = obb1.pos - obb2.pos;

	//	•ª—£Ž² : Ae1
	float rA = D3DXVec2Length(&Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2);
	float L = fabs(D3DXVec2Dot(&Interval, &NAe1));
	if (L > rA + rB)
	{
		return false;
	}
	//	•ª—£Ž² : Ae2
	rA = D3DXVec2Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2);
	L = fabs(D3DXVec2Dot(&Interval, &NAe2));
	if (L > rA + rB)
	{
		return false;
	}
	//	•ª—£Ž² : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2);
	rB = D3DXVec2Length(&Be1);
	L = fabs(D3DXVec2Dot(&Interval, &NBe1));
	if (L > rA + rB)
	{
		return false;
	}
	//	•ª—£Ž² : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2);
	rB = D3DXVec2Length(&Be2);
	L = fabs(D3DXVec2Dot(&Interval, &NBe2));
	if (L > rA + rB)
	{
		return false;
	}
	return true;
}

bool Collision2D( CSprite2D& obj1,  CSprite2D& obj2)
{
	OBB obb1;
	OBB obb2;
	
	D3DXMATRIX rotMtx1;
	D3DXMATRIX rotMtx2;

	D3DXMatrixRotationZ(&rotMtx1, obj1.GetRotation());
	D3DXMatrixRotationZ(&rotMtx2, obj2.GetRotation());

	CreateOBB(&obb1, D3DXVECTOR2(obj1.GetBoxPosition().x, obj1.GetBoxPosition().y), rotMtx1, D3DXVECTOR2(obj1.GetBoxCollisionWidth() / 2.0f, obj1.GetBoxCollisionHeight() / 2.0f));
	CreateOBB(&obb2, D3DXVECTOR2(obj2.GetBoxPosition().x, obj2.GetBoxPosition().y), rotMtx2, D3DXVECTOR2(obj2.GetBoxCollisionWidth() / 2.0f, obj2.GetBoxCollisionHeight() / 2.0f));
	return ObbVSObb2D(obb1, obb2);
}
