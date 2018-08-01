//*****************************************************************************
//!	@file	Stage0Scene.h
//!	@brief	ゲームシーン
//!	@note	2018/07/25
//!	@author
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <list>
#include "FloorSprite.h"
#include "ActionPlayer.h"
#include "Stage0Scene.h"
#include "obb.h"
namespace {
	int BG_WIDTH;

	float cameraX;

	bool isPlayerAction;
	bool isPlayerDrop;

	std::list<CSprite2D> renderList;
	FloorSprite floor1[2];
	FloorSprite floor2;
	ActionPlayer player;

	CSprite2D floor3Tex;
}
void Stage0Scene::Initialize(LPDIRECT3DDEVICE9 lpdev)
{
	floor1[0].Init(lpdev, L"./Texture/stage0_011.tga", D3DXVECTOR3(320, 360, 2), 640, 240, D3DXVECTOR3(240, 445, 2), 480, 70, FloorType_Plane);
	floor1[1].Init(lpdev, L"./Texture/stage0_02.tga", D3DXVECTOR3(960, 360, 2), 640, 240, D3DXVECTOR3(1080, 445, 2), 400, 70, FloorType_Plane);
	floor2.Init(lpdev, L"./Texture/stage0_03.tga", D3DXVECTOR3(640, 360, 3), 1280, 240, D3DXVECTOR3(640, 445, 3), 1280, 70, FloorType_Plane);
	player.Init(lpdev);

	//floor3Tex.Init(lpdev, L"./Texture/box.tga", D3DXVECTOR3(1080, 445, 1), 400, 70, false);
	BG_WIDTH = 1280;
	cameraX = SCREEN_WIDTH / 2.0f;

	isPlayerDrop = false;
	isPlayerAction = true;
}

void Stage0Scene::Finalize()
{
	floor1[0].Exit();
	floor1[1].Exit();
	floor2.Exit();
	player.Exit();

	//floor3Tex.Exit();
}

void Stage0Scene::Update(LPDIRECT3DDEVICE9 lpdev)
{
	D3DXVECTOR3 charaPos;
	D3DXVECTOR3 floorPos;

	if (isPlayerAction)
	{
		player.Update(lpdev);
		if (player.mActionPlayer.GetLocation().x - (player.mActionPlayer.GetWidth() / 2.0f) < 0.0f)
		{
			D3DXVECTOR3 tmpPos = player.mActionPlayer.GetLocation();
			tmpPos.x = player.mActionPlayer.GetWidth() / 2.0f;
			player.mActionPlayer.Translation(tmpPos);
		}
		else if (player.mActionPlayer.GetLocation().x + (player.mActionPlayer.GetWidth() / 2.0f) > (float)BG_WIDTH)
		{
			D3DXVECTOR3 tmpPos = player.mActionPlayer.GetLocation();
			tmpPos.x = BG_WIDTH - player.mActionPlayer.GetWidth() / 2.0f;
			player.mActionPlayer.Translation(tmpPos);
		}
	}

	if (cameraX < player.mActionPlayer.GetLocation().x - SCROLL_DIF) {		// カメラが左に寄っているかチェック
		cameraX = player.mActionPlayer.GetLocation().x - SCROLL_DIF;
	}
	if (cameraX > player.mActionPlayer.GetLocation().x + SCROLL_DIF) {		// カメラが右に寄っているかチェック
		cameraX = player.mActionPlayer.GetLocation().x + SCROLL_DIF;
	}
	if (cameraX < SCREEN_WIDTH / 2.0f) {						// カメラ左移動限界③
		cameraX = SCREEN_WIDTH / 2.0f;
	}
	if (cameraX > BG_WIDTH - SCREEN_WIDTH / 2.0f) {		// カメラ右移動限界④
		cameraX = BG_WIDTH - SCREEN_WIDTH / 2.0f;
	}
	charaPos = player.mActionPlayer.GetLocation();
	charaPos.x = player.mActionPlayer.GetLocation().x - cameraX + SCREEN_WIDTH / 2.0f;
	player.mActionPlayer.SetPosition(charaPos);

	if (player.mlayer == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!Collision2D(player.mActionPlayer, floor1[i].mFloor))
			{
				isPlayerDrop = true;
			}
			else
			{
				isPlayerAction = true;
				isPlayerDrop = false;
				break;
			}
		}
	}
	else if (player.mlayer == 3)
	{
		if (!Collision2D(player.mActionPlayer, floor2.mFloor))
		{
			isPlayerDrop = true;
		}
		else
		{
			isPlayerAction = true;
			isPlayerDrop = false;
		}

	}

	if (isPlayerDrop)
	{
		D3DXVECTOR3 tpos = player.mActionPlayer.GetLocation();
		tpos.y += 2;
		isPlayerAction = false;
		player.mActionPlayer.Translation(tpos);
	}
	for (int i = 0; i < 2; i++)
	{
		floorPos = floor1[i].mFloor.GetLocation();
		floorPos.x = floor1[i].mFloor.GetLocation().x - cameraX + SCREEN_WIDTH / 2.0f;
		floor1[i].mFloor.SetPosition(floorPos);
		floor1[i].Update(lpdev);
		floor1[i].mFloor.Update(lpdev);
	}
	floorPos = floor2.mFloor.GetLocation();
	floorPos.x = floor2.mFloor.GetLocation().x - cameraX + SCREEN_WIDTH / 2.0f;
	floor2.mFloor.SetPosition(floorPos);
	floor2.Update(lpdev);
	floor2.mFloor.Update(lpdev);
	player.mActionPlayer.Update(lpdev);


	//floorPos = floor3Tex.GetLocation();
	//floorPos.x = floor3Tex.GetLocation().x - cameraX + SCREEN_WIDTH / 2.0f;
	//floor3Tex.SetPosition(floorPos);
	//floor3Tex.Update(lpdev);
}

void Stage0Scene::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	for (int i = 0; i < 2; i++)
	{
		if (floor1[0].mFloor.GetZBuffer() >= player.mlayer)
		{
			renderList.push_back(floor1[i].mFloor);
		}
	}

	if (floor2.mFloor.GetZBuffer() >= player.mlayer)
	{
		renderList.push_back(floor2.mFloor);
	}
	renderList.push_back(player.mActionPlayer);

	//renderList.push_back(floor3Tex);
	renderList.sort(CompSprite);
	for (std::list<CSprite2D>::iterator iterList = renderList.begin(); iterList != renderList.end(); iterList++)
	{
	iterList->Draw(lpdev);
	}
	renderList.clear();
}
