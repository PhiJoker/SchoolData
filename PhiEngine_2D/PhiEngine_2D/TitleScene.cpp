//*****************************************************************************
//!	@file	TitleScene.h
//!	@brief	タイトル
//!	@note	2018/07/25
//!	@author
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include "CSprite2D.h"


namespace {
	CSprite2D titleBG[47];
	int dt = 0;
	//std::list<CSprite2D> renderList;
	int flag = 0;
}

void TitleScene::Initialize(LPDIRECT3DDEVICE9 lpdev)
{
	//dt = 0;
	flag = 0;
	titleBG[0].Init(lpdev, L"./Logo/logo0000.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[1].Init(lpdev, L"./Logo/logo0001.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[2].Init(lpdev, L"./Logo/logo0002.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[3].Init(lpdev, L"./Logo/logo0003.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[4].Init(lpdev, L"./Logo/logo0004.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[5].Init(lpdev, L"./Logo/logo0005.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[6].Init(lpdev, L"./Logo/logo0006.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[7].Init(lpdev, L"./Logo/logo0007.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[8].Init(lpdev, L"./Logo/logo0008.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[9].Init(lpdev, L"./Logo/logo0009.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[10].Init(lpdev, L"./Logo/logo0010.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[11].Init(lpdev, L"./Logo/logo0011.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[12].Init(lpdev, L"./Logo/logo0012.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[13].Init(lpdev, L"./Logo/logo0013.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[14].Init(lpdev, L"./Logo/logo0014.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[15].Init(lpdev, L"./Logo/logo0015.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[16].Init(lpdev, L"./Logo/logo0016.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[17].Init(lpdev, L"./Logo/logo0017.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[18].Init(lpdev, L"./Logo/logo0018.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[19].Init(lpdev, L"./Logo/logo0019.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[20].Init(lpdev, L"./Logo/logo0020.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[21].Init(lpdev, L"./Logo/logo0021.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[22].Init(lpdev, L"./Logo/logo0022.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[23].Init(lpdev, L"./Logo/logo0023.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[24].Init(lpdev, L"./Logo/logo0024.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[25].Init(lpdev, L"./Logo/logo0025.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[26].Init(lpdev, L"./Logo/logo0026.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[27].Init(lpdev, L"./Logo/logo0027.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[28].Init(lpdev, L"./Logo/logo0028.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[29].Init(lpdev, L"./Logo/logo0029.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[30].Init(lpdev, L"./Logo/logo0030.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[31].Init(lpdev, L"./Logo/logo0031.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[32].Init(lpdev, L"./Logo/logo0032.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[33].Init(lpdev, L"./Logo/logo0033.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[34].Init(lpdev, L"./Logo/logo0034.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[35].Init(lpdev, L"./Logo/logo0035.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[36].Init(lpdev, L"./Logo/logo0036.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[37].Init(lpdev, L"./Logo/logo0037.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[38].Init(lpdev, L"./Logo/logo0038.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[39].Init(lpdev, L"./Logo/logo0039.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[40].Init(lpdev, L"./Logo/logo0040.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[41].Init(lpdev, L"./Logo/logo0041.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[42].Init(lpdev, L"./Logo/logo0042.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[43].Init(lpdev, L"./Logo/logo0043.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[44].Init(lpdev, L"./Logo/logo0044.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[45].Init(lpdev, L"./Logo/logo0045.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
	titleBG[46].Init(lpdev, L"./Logo/logo0046.tga", D3DXVECTOR3(320, 240, 1), SCREEN_WIDTH, SCREEN_HEIGHT, false);
}

void TitleScene::Finalize()
{
	for (int i = 0; i < 47; i++)
	{
		titleBG[i].Exit();
	}
}

void TitleScene::Update(LPDIRECT3DDEVICE9 lpdev)
{
	for (int i = 0; i < 47; i++)
	{
		titleBG[i].Update(lpdev);
	}
	dt++;
	if (dt > 230)
	{
		dt = 230;
		flag++;
	}
	if (flag>=60)
	{
		mSceneChanger->ChangeScene(eScene_Stage0);//シーンをゲーム画面に変更
	}
}

void TitleScene::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	titleBG[dt/5].Draw(lpdev);
	/*renderList.push_back(titleBG);
	renderList.sort(CompSprite);
	for (std::list<CSprite2D>::iterator iterList = renderList.begin(); iterList != renderList.end(); iterList++)
	{
		iterList->Draw(lpdev);
	}
	renderList.clear();*/
}

//*****************************************************************************
//	End of file.
//*****************************************************************************