//*****************************************************************************
//!	@file	ISceneChanger.h
//!	@brief	
//!	@note	2018/07/20
//!	@author
//*****************************************************************************
#pragma once
#ifndef _ISCENECHANGER_H_
#define _ISCENECHANGER_H_

typedef enum {
	eScene_Title,	//	メニュー画面
	eScene_Stage0,	//	Stage0画面
	eScene_Config,	//	設定画面

	eScene_None,    //	無し
} eScene;

//	シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	ISceneChanger() {}
	virtual ~ISceneChanger() = 0 {}
	virtual void ChangeScene(eScene NextScene) = 0 {}//	指定シーンに変更する
};

#endif