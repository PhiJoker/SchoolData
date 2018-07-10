//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSpriteèàóùÉNÉâÉX
//!	@note	
//!	@author	údäCü∑	2018-07-09
//*****************************************************************************
#pragma once
#ifndef _CSPRITE2D_H_
#define _CSPRITE2D_H_

#include	"GameUtil.h"



class CSprite2D
{
private:
	D3DXMATRIX		m_Mat;

	D3DXVECTOR3		m_angle;
	D3DXVECTOR3		m_trans;


	bool			m_isActive;

public:
	CSprite2D(LPCWSTR filename);
	~CSprite2D();

	void Init(LPDIRECT3DDEVICE9 lpdev);

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

};



#endif