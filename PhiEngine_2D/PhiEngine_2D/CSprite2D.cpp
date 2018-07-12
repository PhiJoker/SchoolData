//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSpriteˆ—ƒNƒ‰ƒX
//!	@note	
//!	@author	œdŠCŸ·	2018-07-09
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "CSprite2D.h"

void CSprite2D::Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale)
{
	m_tex = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9));
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(lpdev, filename, m_tex);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Err", L"Texture erro", MB_OK);
	}
	m_v[0] = { -1.0f,1.0f,0.0f,0,0 };
	m_v[1] = { 1.0f,1.0f,0.0f,1,0 };
	m_v[2] = { -1.0f,-1.0f,0.0f,0,1 };
	m_v[3] = { 1.0f,-1.0f,0.0f,1,1 };

	MakeWorldMatrix(m_MatTotal, position, rotation, scale);
}

void CSprite2D::Update(LPDIRECT3DDEVICE9 lpdev)
{
	static D3DXVECTOR3 tmpPos = { 0.0f, 0.0f, 0.0f };
	static D3DXVECTOR3 tmpRotate = { 0.0f, 0.0f, 0.0f };
	static D3DXVECTOR3 tmpScale = { 1.0f, 1.0f, 1.0f };

	if (GetKeyboardPress(DIK_LEFT)) {
		tmpPos.x -= 0.1f;
	}
	MakeWorldMatrix(m_Mat,m_MatTotal, tmpPos,tmpRotate,tmpScale);

}

void CSprite2D::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	lpdev->SetTransform(D3DTS_WORLD, &m_MatTotal);
	lpdev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	lpdev->SetTexture(0, *m_tex);
	lpdev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_v, sizeof(VERTEX2D));
}

void CSprite2D::Exit()
{

	if (m_tex != NULL)
	{
		(*m_tex)->Release();
		free(m_tex);
		m_tex = NULL;
	}
}

//*****************************************************************************
//	End of file.
//*****************************************************************************