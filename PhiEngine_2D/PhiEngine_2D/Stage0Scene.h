//*****************************************************************************
//!	@file	Stage0Scene.h
//!	@brief	�Q�[���V�[��
//!	@note	2018/07/25
//!	@author	�d�C��
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

	void Initialize(LPDIRECT3DDEVICE9 lpdev) override;	//�����������͎������Ă����Ȃ��Ă�����
	void Finalize() override;							//�I�������͎������Ă����Ȃ��Ă�����
	void Update(LPDIRECT3DDEVICE9 lpdev) override;		//�X�V�����͕K���p����Ŏ�������
	void Draw(LPDIRECT3DDEVICE9 lpdev) override;		//�`�揈���͕K���p����Ŏ�������

};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif