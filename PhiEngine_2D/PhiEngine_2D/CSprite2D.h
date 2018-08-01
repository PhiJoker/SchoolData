//*****************************************************************************
//!	@file	CSprite2D.cpp
//!	@brief	2DSprite�����N���X
//!	@note	
//!	@author	�d�C��	2018-07-09
//*****************************************************************************
#pragma once
#ifndef _CSPRITE2D_H_
#define _CSPRITE2D_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	"GameUtil.h"
//#include	"MathUtil.h"

#define		RIGHT		0;
#define		LEFT		1;
//-----------------------------------------------------------------------------
//	�\���̒�`
//-----------------------------------------------------------------------------

// ���_�f�[�^�t�H�[�}�b�g
typedef struct tagVERTEX2D
{
	float x, y, z;
	float rhw;
	D3DCOLOR c;
	float u, v;
}VERTEX2D;

//	�A�j���[�V�����N���b�v
typedef struct tagAnimationClip
{
	//	UV���_
	float originU;
	float originV;

	//	�����T�C�Y
	float divU;
	float divV;

	//	�t���[������
	unsigned int frameNum;
	//	����(�t���[��)
	unsigned int frameTime;
}AnimationClip;

//=============================================================================
//!	@class	CSprite2D
//!	@brief	CSprite2D�N���X
//=============================================================================
class CSprite2D
{
public:
	int					m_direction;
private:
	bool				m_isActive;		//	

	VERTEX2D			m_v[4];			//	

	D3DCOLOR			m_color;
	int					m_width;		//	��
	int					m_height;		//	����

	float				m_angle;		//	��]�p�x
	D3DXVECTOR3			m_position;		//	���S���W(��ʏ�)
	D3DXVECTOR3			m_location;		//	���S���W(�t�B�[���h)

	int					m_boxWidth;		//	�����蔻��̕�
	int					m_boxHeight;	//	�����蔻��̍���
	D3DXVECTOR3			m_boxPosition;	//	�����蔻��̒��S���W

	LPDIRECT3DTEXTURE9*	m_pTex;			//	�e�N�X�`��
	
	//	�t���[���A�j���[�V����
	AnimationClip*		m_frameList;
	int					m_frameCnt;
	int					m_actionID;

	bool				m_isTurn;
	bool				m_isAnimation;

public:

	//	�R���X�g���N�^
	CSprite2D() {
	}		

	//	�f�X�g���N�^
	~CSprite2D(){}						

	void Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3 position, int width, int height, bool isTurn);

	void SetActive(bool isActive) { m_isActive = isActive; }
	bool GetActive() { return m_isActive; }

	void InitAnimation(AnimationClip clip[], int actionNum);
	void SetAnimationID(int id) { m_actionID = id; }

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

	D3DXVECTOR3 GetLocation() { return m_location; }
	void Translation(D3DXVECTOR3& position);
	D3DXVECTOR3 GetPosition() { return m_position; }
	void SetPosition(D3DXVECTOR3 pos) { m_position = pos; }

	void Rotate(float angle) { m_angle = angle; }
	float GetAngle() { return m_angle; }
	// ��]�l�i���W�A���j
	float GetRotation() { return  D3DX_PI*m_angle / 180.0f; }

	void SetSize(int w, int h) { m_width = w; m_height = h; }
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	
	void SetZBuffer(float z) { m_location.z = z; }
	float GetZBuffer() { return m_location.z; }

	void SetColor(D3DCOLOR c) { m_color = c; }
	D3DCOLOR GetColor() { return m_color; }

	void SetBoxPosition(D3DXVECTOR3 pos) { m_boxPosition = pos; }
	D3DXVECTOR3 GetBoxPosition() { return m_boxPosition; }
	void SetBoxCollision(int w, int h) { m_boxWidth = w; m_boxHeight = h; }
	int GetBoxCollisionWidth() { return m_boxWidth; }
	int GetBoxCollisionHeight() { return m_boxHeight; }
};

bool CompSprite(CSprite2D a1, CSprite2D a2);

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif