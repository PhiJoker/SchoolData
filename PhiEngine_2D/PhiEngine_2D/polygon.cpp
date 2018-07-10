#include "polygon.h"

D3DXMATRIX	g_matrix;		// ワールド変換行列
VERTEX2D v[] = {
	{-0.5f,0.5f,0.0f,0,0},
	{ 0.5f,0.5f,0.0f,1,0 },
	{ -0.5f,-0.5f,0.0f,0,1 },
	{ 0.5f,-0.5f,0.0f,1,1 }
};

void Draw2dPolygon(LPDIRECT3DDEVICE9 lpdevice, LPDIRECT3DTEXTURE9* tex)
{
	// 単位行列にする
	//D3DXMatrixIdentity(&g_matrix);
	//D3DXMatrixTranslation(&g_matrix, 200, 0, 0);
	// ワールド変換行列をセット
	lpdevice->SetTransform(D3DTS_WORLD, &g_matrix);

	lpdevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	lpdevice->SetTexture(0, *tex);
	lpdevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(VERTEX2D));
}

LPDIRECT3DTEXTURE9* LoadTexture(LPDIRECT3DDEVICE9 lpdevice, LPCWSTR name, LPDIRECT3DTEXTURE9* tex)
{
	tex = (LPDIRECT3DTEXTURE9 *)malloc(sizeof(LPDIRECT3DTEXTURE9));
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(lpdevice, name, tex);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Err", L"erro", MB_OK);
		return false;
	}

	return tex;
}

bool ReleaseTexture(LPDIRECT3DTEXTURE9* tex)
{
	if (tex != NULL)
	{
		(*tex)->Release();
		free(tex);
		tex = NULL;
	}
	return true;
}

void MovePolygon(float x, float y, float angle, float sx, float sy)
{
	D3DXMATRIX mt;
	D3DXMatrixScaling(&mt, sx, sy, 1.0f);
	D3DXMATRIX rz;
	D3DXMatrixRotationZ(&rz, angle);
	D3DXMatrixTranslation(&g_matrix, x, y, 0);

	//	拡大縮小＊回転＊移動
	g_matrix = mt*rz*g_matrix;
}
