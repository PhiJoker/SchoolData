//*****************************************************************************
//!	@file	TitleScene.h
//!	@brief	�^�C�g��
//!	@note	2018/07/25
//!	@author	�d�C��
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

	void Initialize(LPDIRECT3DDEVICE9 lpdev) override;	//�����������͎������Ă����Ȃ��Ă�����
	void Finalize() override;							//�I�������͎������Ă����Ȃ��Ă�����
	void Update(LPDIRECT3DDEVICE9 lpdev) override;		//�X�V�����͕K���p����Ŏ�������
	void Draw(LPDIRECT3DDEVICE9 lpdev) override;		//�`�揈���͕K���p����Ŏ�������

};

//*****************************************************************************
//	End of file.
//*****************************************************************************
#endif