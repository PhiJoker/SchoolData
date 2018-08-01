//*****************************************************************************
//!	@file	SceneManager.h
//!	@brief	�V�[���Ǘ��N���X
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

	void Initialize(LPDIRECT3DDEVICE9 lpdev) override;//������
	void Finalize() override;//�I������
	void Update(LPDIRECT3DDEVICE9 lpdev) override;//�X�V
	void Draw(LPDIRECT3DDEVICE9 lpdev) override;//�`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;
};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif
