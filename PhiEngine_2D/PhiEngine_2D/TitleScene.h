//*****************************************************************************
//!	@file	TitleScene.h
//!	@brief	タイトル
//!	@note	2018/07/25
//!	@author	彭海濤
//*****************************************************************************
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "SceneBase.h"

class TitleScene:public SceneBase
{
public:
	TitleScene(ISceneChanger* changer) :SceneBase(changer) {}
	virtual ~TitleScene() {}

	void Initialize(LPDIRECT3DDEVICE9 lpdev) override;	//初期化処理は実装してもしなくてもいい
	void Finalize() override;							//終了処理は実装してもしなくてもいい
	void Update(LPDIRECT3DDEVICE9 lpdev) override;		//更新処理は必ず継承先で実装する
	void Draw(LPDIRECT3DDEVICE9 lpdev) override;		//描画処理は必ず継承先で実装する

};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif