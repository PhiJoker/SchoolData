//*****************************************************************************
//!	@file	SceneManager.h
//!	@brief	シーン管理クラス
//!	@note	2018/07/25
//!	@author
//*****************************************************************************
#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "SceneBase.h"
#include "TitleScene.h"
#include "Stage0Scene.h"

class SceneManager :public ISceneChanger, Task
{
private:
	SceneBase* mScene;
	eScene mNextScene;
public:
	SceneManager();
	~SceneManager() {}

	void Initialize(LPDIRECT3DDEVICE9 lpdev) override;//初期化
	void Finalize() override;//終了処理
	void Update(LPDIRECT3DDEVICE9 lpdev) override;//更新
	void Draw(LPDIRECT3DDEVICE9 lpdev) override;//描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;
};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif
