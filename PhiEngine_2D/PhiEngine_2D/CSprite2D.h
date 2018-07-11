//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSprite処理クラス
//!	@note	
//!	@author	彭海濤	2018-07-09
//*****************************************************************************
#pragma once
#ifndef _CSPRITE2D_H_
#define _CSPRITE2D_H_

#include	"GameUtil.h"



class CSprite2D
{
private:
	D3DXMATRIX		m_Mat;				//	変換行列
	D3DXMATRIX		m_MatTotal;			//	積算行列

	D3DXVECTOR3		m_angle;			//	回転角度
	D3DXVECTOR3		m_trans;			//	移動量

	LPDIRECT3DTEXTURE9* m_tex;			//	テクスチャ
	bool			m_isActive;			//	

public:
	CSprite2D(LPCWSTR filename);
	~CSprite2D();

	void Init(LPDIRECT3DDEVICE9 lpdev);

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

};



#endif