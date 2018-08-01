//*****************************************************************************
//!	@file	SceneBase.h
//!	@brief	状態遷移基本クラス
//!	@note	2018/07/25
//!	@author
//*****************************************************************************
#pragma once
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Task.h"
#include "ISceneChanger.h"

class SceneBase : public Task{
protected:
	int mImageHandle;                //画像ハンドル格納用変数
	ISceneChanger* mSceneChanger;    //クラス所有元にシーン切り替えを伝えるインターフェイス

public:
	SceneBase(ISceneChanger* changer) :mImageHandle(0) { mSceneChanger = changer; }
	virtual ~SceneBase() {}
	virtual void Initialize(LPDIRECT3DDEVICE9 lpdev) override {}    //初期化処理は実装してもしなくてもいい
	virtual void Finalize() override {}								//終了処理は実装してもしなくてもいい
	virtual void Update(LPDIRECT3DDEVICE9 lpdev) override {}		//更新処理は必ず継承先で実装する
	virtual void Draw(LPDIRECT3DDEVICE9 lpdev) override {}			//描画処理は必ず継承先で実装する
};


#endif