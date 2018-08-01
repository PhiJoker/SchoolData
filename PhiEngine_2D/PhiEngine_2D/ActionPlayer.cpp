//*****************************************************************************
//!	@file	ActionPlayer.cpp
//!	@brief	アクションシーンのプレイヤー処理
//!	@note	
//!	@author	彭海濤	2018-07-30
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "ActionPlayer.h"


//*****************************************************************************
//	End of file.
//*****************************************************************************

void ActionPlayer::Init(LPDIRECT3DDEVICE9 lpdev)
{
	mActionPlayer.Init(lpdev, L"./Texture/player_test.tga", D3DXVECTOR3(150, 100, 1), 200, 200, true);
	AnimationClip tmpc[2] = {
		{ 0,0,0.125f,0.5f,2,20 },
		{ 0,0.5f,0.125f,0.5f,6,20 }
	};
	mActionPlayer.InitAnimation(tmpc, 2);
	mlayer = 2;
	isUpKey = true;
	isDownKey = true;
}

void ActionPlayer::Update(LPDIRECT3DDEVICE9 lpdev)
{
	D3DXVECTOR3 tpos = mActionPlayer.GetLocation();
	if (GetKeyboardPress(DIK_LEFT))
	{
		tpos.x -= CHARA_VEL;
		mActionPlayer.m_direction = 1;
		mActionPlayer.SetAnimationID(1);
		mActionPlayer.Translation(tpos);
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		tpos.x += CHARA_VEL;
		mActionPlayer.m_direction = 0;
		mActionPlayer.SetAnimationID(1);
		mActionPlayer.Translation(tpos);
	}
	else if (GetKeyboardPress(DIK_UP) && isUpKey == true)
	{
		if (mlayer < 4)
		{
			mlayer++;
			isUpKey = false;
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) && isDownKey == true)
	{
		if (mlayer > 2)
		{
			mlayer--;
			isDownKey = false;
		}
	}
	else
	{
		mActionPlayer.SetAnimationID(0);
	}

	if (GetKeyboardRelease(DIK_UP))
	{
		isUpKey = true;
	}
	else if (GetKeyboardRelease(DIK_DOWN))
	{
		isDownKey = true;
	}

	//mActionPlayer.Update(lpdev);
}

void ActionPlayer::Exit()
{
	mActionPlayer.Exit();
}
