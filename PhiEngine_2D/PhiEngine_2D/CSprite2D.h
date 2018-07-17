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

<<<<<<< HEAD
#define		RIGHT		0;
#define		LEFT		1;
=======
>>>>>>> dev
//-----------------------------------------------------------------------------
//	構造体定義
//-----------------------------------------------------------------------------

// 頂点データフォーマット
typedef struct tagVERTEX2D
{
	float x, y, z;
<<<<<<< HEAD
	float rhw;
	float u, v;
}VERTEX2D;

//	アニメーションクリップ
typedef struct tagAnimationClip
{
	//	UV原点
	float originU;
	float originV;

	//	分割サイズ
	float divU;
	float divV;

	//	フレーム数量
	unsigned int frameNum;
	//	時間(フレーム)
	unsigned int frameTime;
}AnimationClip;
=======
	float u, v;
}VERTEX2D;
>>>>>>> dev

//=============================================================================
//!	@class	CSprite2D
//!	@brief	CSprite2Dクラス
//=============================================================================
class CSprite2D
{

public:
	bool				m_isActive;		//	
	int					m_actionID;

private:
	VERTEX2D			m_v[4];			//	

	D3DXMATRIX			m_Mat;			//	変換行列
	D3DXMATRIX			m_MatTotal;		//	積算行列

<<<<<<< HEAD
	D3DXVECTOR3			m_rotation;		//	回転角度
	D3DXVECTOR3			m_position;		//	中心座標
	D3DXVECTOR3			m_scale;		//	スケール量

	LPDIRECT3DTEXTURE9*	m_pTex;			//	テクスチャ
	
	//	フレームアニメーション
	AnimationClip*		m_frameList;
	int					m_direction;
	int					m_frameCnt;

	bool				m_isTurn;
	bool				m_isAnimation;

public:

	//	コンストラクタ
	CSprite2D() {
		m_direction = RIGHT;
		m_actionID = 0; 
		m_frameCnt = 0;
	}		

	//	デストラクタ
	~CSprite2D(){}						

	void Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, bool isTurn);

	void SetAnimation(AnimationClip clip[], int actionNum);
=======
	D3DXVECTOR3			m_angle;		//	回転角度
	D3DXVECTOR3			m_trans;		//	移動量
	D3DXVECTOR3			m_scale;		//	スケール量

	LPDIRECT3DTEXTURE9* m_tex;			//	テクスチャ
	bool				m_isActive;		//	

public:
	CSprite2D(){}						//	コンストラクタ
	~CSprite2D(){}						//	デストラクタ

	void Init(LPDIRECT3DDEVICE9 lpdev, LPCWSTR filename, D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale);
>>>>>>> dev

	void Update(LPDIRECT3DDEVICE9 lpdev);

	void Draw(LPDIRECT3DDEVICE9 lpdev);
	
	void Exit();

	void Translation(D3DXVECTOR3& position) { m_position = position; }
	void Rotate(D3DXVECTOR3& angle) { m_rotation = angle; }
	void Scaling(D3DXVECTOR3& scale) { m_scale = scale; }

	D3DXVECTOR3 GetPosition() { return m_position; }
	D3DXVECTOR3 GetRotation() { return m_rotation; }
	D3DXVECTOR3 GetScale() { return m_scale; }
};

<<<<<<< HEAD

=======
>>>>>>> dev
//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif