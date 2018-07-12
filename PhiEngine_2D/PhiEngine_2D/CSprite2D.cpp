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
	m_pTex = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9));
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(lpdev, filename, m_pTex);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Err", L"Texture erro", MB_OK);
	}
	m_v[0] = { 0.0f,0.0f,0.0f,1,0,0 };
	m_v[1] = { 100.0f,0.0f,0.0f,1,1,0 };
	m_v[2] = { 0.0f,100.0f,0.0f,1,0,1 };
	m_v[3] = { 100.0f,100.0f,0.0f,1,1,1 };

	m_position = position;
	m_rotation = rotation;
	m_scale = scale;

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
	D3DXVECTOR3 trans = { 0,0,0 };
	D3DXVECTOR3 angles = { 0,0,0 };
	D3DXVECTOR3 scales = { 1,1,1 };
	if (GetKeyboardPress(DIK_LEFT)) {
		trans.x -= 10;
		m_position.x -= 10;
		m_direction = (m_isTurn ? 1 : 0);
	}
	if (GetKeyboardPress(DIK_RIGHT)) {
		trans.x += 10;
		m_position.x += 10;
		m_direction = (m_isTurn ? 0 : 0);
	}

	//MakeWorldMatrix(m_Mat, m_MatTotal, trans, angles, scales);
	MakeWorldMatrix(m_MatTotal, m_position, m_rotation, m_scale);
}

void CSprite2D::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	lpdev->SetTransform(D3DTS_WORLD, &m_MatTotal);
	lpdev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	lpdev->SetTexture(0, *m_pTex);
	
	
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

	if (m_pTex != NULL)
	{
		(*m_pTex)->Release();
		free(m_pTex);
		m_pTex = NULL;
	}
}

//*****************************************************************************
//	End of file.
//*****************************************************************************