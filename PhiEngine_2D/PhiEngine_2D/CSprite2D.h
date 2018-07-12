//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSprite処理クラス
//!	@note	
//!	@author	彭海濤	2018-07-09
//*****************************************************************************
#pragma once
#ifndef _CSPRITE2D_H_
#define _CSPRITE2D_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	"GameUtil.h"
#include	"MathUtil.h"

//-----------------------------------------------------------------------------
//	構造体定義
//-----------------------------------------------------------------------------

// 頂点データフォーマット
typedef struct tagVERTEX2D
{
	float x, y, z;
	float u, v;
}VERTEX2D;

//=============================================================================
//!	@class	CSprite2D
//!	@brief	CSprite2Dクラス
//=============================================================================
class CSprite2D
{
private:
	VERTEX2D			m_v[4];			//	

	D3DXMATRIX			m_Mat;			//	変換行列
	D3DXMATRIX			m_MatTotal;		//	積算行列

	D3DXVECTOR3			m_rotation;		//	回転角度
	D3DXVECTOR3			m_position;		//	移動量
	D3DXVECTOR3			m_scale;		//	スケール量

	LPDIRECT3DTEXTURE9*	m_tex;			//	テクスチャ
	bool				m_isActive;		//	

public:
	CSprite2D(){}						//	コンストラクタ
	~CSprite2D(){}						//	デストラクタ

	void Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale);

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

};


//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif