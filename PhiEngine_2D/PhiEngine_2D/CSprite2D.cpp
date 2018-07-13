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

void CSprite2D::Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, bool isTurn)
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

	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_scale = { 1.0f, 1.0f, 1.0f };

	m_isAnimation = false;
	m_isTurn = isTurn;

	MakeWorldMatrix(m_MatTotal, position, rotation, scale);
}

void CSprite2D::SetAnimation(AnimationClip clip[], int actionNum)
{
	m_frameList = new AnimationClip[actionNum];
	memcpy(m_frameList, clip, sizeof(AnimationClip)*actionNum);

	m_isAnimation = true;
}

void CSprite2D::Update(LPDIRECT3DDEVICE9 lpdev)
{
	if (GetKeyboardPress(DIK_LEFT)) {
		m_position.x -= 0.1f;
		m_direction = (m_isTurn ? 1 : 0);
	}
	if (GetKeyboardPress(DIK_RIGHT)) {
		m_position.x += 0.1f;
		m_direction = (m_isTurn ? 0 : 0);
	}

	MakeWorldMatrix(m_Mat, m_MatTotal, m_position, m_rotation, m_scale);

}

void CSprite2D::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	lpdev->SetTransform(D3DTS_WORLD, &m_Mat);
	lpdev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	lpdev->SetTexture(0, *m_tex);
	
	if (m_isAnimation)
	{
		if (m_frameCnt >= m_frameList[m_actionID].frameNum*m_frameList[m_actionID].frameTime)
		{
			m_frameCnt = 0;
		}
		float tmpU = m_frameList[m_actionID].originU + (m_frameCnt / m_frameList[m_actionID].frameTime)* m_frameList[m_actionID].divU;

		m_v[0].u = tmpU;
		m_v[0].v = m_frameList[m_actionID].originV;

		m_v[1].u = tmpU + m_frameList[m_actionID].divU;
		m_v[1].v = m_frameList[m_actionID].originV;

		m_v[2].u = tmpU;
		m_v[2].v = m_frameList[m_actionID].originV + m_frameList[m_actionID].divV;

		m_v[3].u = tmpU + m_frameList[m_actionID].divU;
		m_v[3].v = m_frameList[m_actionID].originV + m_frameList[m_actionID].divV;

		m_frameCnt++;
	}
	else
	{
		m_v[0].u = (m_direction ? 1 : 0);
		m_v[2].u = (m_direction ? 1 : 0);
		m_v[1].u = (m_direction ? 0 : 1);
		m_v[3].u = (m_direction ? 0 : 1);
	}
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