//======================================================================
//!	@file	polygon.h
//!	@brief	
//!	@note	Polygon描画
//!	@author	彭海濤	2018-06-22
//======================================================================
#pragma once
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include	<d3dx9.h>
// 頂点データフォーマット
typedef struct tagVERTEX2D
{
	float x, y, z;
	float u, v;
}VERTEX2D;


void Draw2dPolygon(LPDIRECT3DDEVICE9 lpdevice,  LPDIRECT3DTEXTURE9* tex);
LPDIRECT3DTEXTURE9* LoadTexture(LPDIRECT3DDEVICE9 lpdevice,LPCWSTR, LPDIRECT3DTEXTURE9 *);
bool ReleaseTexture(LPDIRECT3DTEXTURE9 *);

void MovePolygon(float x, float y, float angle, float sx, float sy);
#endif

