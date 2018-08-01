//*****************************************************************************
//!	@file	Stage0Scene.h
//!	@brief	ゲームシーン
//!	@note	2018/07/25
//!	@author	彭海濤
//*****************************************************************************
#ifndef _STAGE0SCENE_H_
#define _Stage0SCENE_H_
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "SceneBase.h"
class Stage0Scene :public SceneBase
{
public:
	Stage0Scene(ISceneChanger* changer) :SceneBase(changer) {}
	virtual ~Stage0Scene() {}

	void Initialize(LPDIRECT3DDEVICE9 lpdev) override;	//初期化処理は実装してもしなくてもいい
	void Finalize() override;							//終了処理は実装してもしなくてもいい
	void Update(LPDIRECT3DDEVICE9 lpdev) override;		//更新処理は必ず継承先で実装する
	void Draw(LPDIRECT3DDEVICE9 lpdev) override;		//描画処理は必ず継承先で実装する

};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif