//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSpriteèàóùÉNÉâÉX
//!	@note	
//!	@author	údäCü∑	2018-07-09
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "CSprite2D.h"

void CSprite2D::Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3 position, int width, int height, bool isTurn)
{
	m_pTex = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9));
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(lpdev, filename, m_pTex);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Err", L"Texture erro", MB_OK);
	}

	m_position = position;
	m_location = position;
	m_boxPosition = position;
	m_angle = 0;
	m_width = width;
	m_height = height;
	m_boxWidth = width;
	m_boxHeight = height;
	m_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_isAnimation = false;
	m_isTurn = isTurn;

	m_direction = RIGHT;
	m_actionID = 0;
	m_frameCnt = 0;
}

void CSprite2D::InitAnimation(AnimationClip clip[], int actionNum)
{
	m_frameList = new AnimationClip[actionNum];
	memcpy(m_frameList, clip, sizeof(AnimationClip)*actionNum);

	m_isAnimation = true;
}

void CSprite2D::Update(LPDIRECT3DDEVICE9 lpdev)
{
	m_v[0] = { (float)-m_width / 2,(float)-m_height / 2,0,1,m_color,0,0 };
	m_v[1] = { (float)m_width / 2,(float)-m_height / 2,0,1,m_color,1,0 };
	m_v[2] = { (float)-m_width / 2,(float)m_height / 2,0,1,m_color,0,1 };
	m_v[3] = { (float)m_width / 2,(float)m_height / 2,0,1,m_color,1,1 };

	float rorate = D3DX_PI*m_angle / 180.0f;
	for (int i = 0; i < 4; i++)
	{
		float x = m_v[i].x*cosf(rorate) - m_v[i].y*sinf(rorate);
		float y = m_v[i].x*sinf(rorate) + m_v[i].y*cosf(rorate);

		m_v[i].x = x + m_position.x;
		m_v[i].y = y + m_position.y;
	}

	if (m_isAnimation)
	{
		if (m_frameCnt >= m_frameList[m_actionID].frameNum*m_frameList[m_actionID].frameTime)
		{
			m_frameCnt = 0;
		}
		//	ÉtÉåÅ[ÉÄÇÃU
		float tmpU = m_frameList[m_actionID].originU + (m_frameCnt / m_frameList[m_actionID].frameTime)* m_frameList[m_actionID].divU;

		m_v[0].v = m_frameList[m_actionID].originV;
		m_v[1].v = m_frameList[m_actionID].originV;
		m_v[2].v = m_frameList[m_actionID].originV + m_frameList[m_actionID].divV;
		m_v[3].v = m_frameList[m_actionID].originV + m_frameList[m_actionID].divV;
		if (m_direction == 0)
		{
			m_v[0].u = tmpU;
			m_v[1].u = tmpU + m_frameList[m_actionID].divU;
			m_v[2].u = tmpU;
			m_v[3].u = tmpU + m_frameList[m_actionID].divU;
		}
		else
		{
			m_v[0].u = tmpU + m_frameList[m_actionID].divU;
			m_v[1].u = tmpU;
			m_v[2].u = tmpU + m_frameList[m_actionID].divU;
			m_v[3].u = tmpU;
		}
		m_frameCnt++;
	}
	else
	{
		m_v[0].u = (m_direction ? 1.0f : 0.0f);
		m_v[2].u = (m_direction ? 1.0f : 0.0f);
		m_v[1].u = (m_direction ? 0.0f : 1.0f);
		m_v[3].u = (m_direction ? 0.0f : 1.0f);
	}
}

void CSprite2D::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	lpdev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	lpdev->SetTexture(0, *m_pTex);
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
	if (m_isAnimation)
	{
		delete m_frameList;
	}
}

void CSprite2D::Translation(D3DXVECTOR3 & position)
{
	D3DXVECTOR3 tmpPos, oldPos, boxPos;
	oldPos = m_location;
	tmpPos.x = position.x - oldPos.x;
	tmpPos.y = position.y - oldPos.y;
	boxPos.x = tmpPos.x + m_boxPosition.x;
	boxPos.y = tmpPos.y + m_boxPosition.y;
	boxPos.z = position.z;
	m_location = position;
	m_boxPosition = boxPos;
}

bool CompSprite(CSprite2D a1, CSprite2D a2)
{
	if (a1.GetZBuffer() <= a2.GetZBuffer())
	{
		return false;
	}
	else
	{
		return true;
	}
}
//*****************************************************************************
//	End of file.
//*****************************************************************************