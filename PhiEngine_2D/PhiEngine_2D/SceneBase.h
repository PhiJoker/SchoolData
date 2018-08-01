//*****************************************************************************
//!	@file	SceneBase.h
//!	@brief	��ԑJ�ڊ�{�N���X
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
	int mImageHandle;                //�摜�n���h���i�[�p�ϐ�
	ISceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public:
	SceneBase(ISceneChanger* changer) :mImageHandle(0) { mSceneChanger = changer; }
	virtual ~SceneBase() {}
	virtual void Initialize(LPDIRECT3DDEVICE9 lpdev) override {}    //�����������͎������Ă����Ȃ��Ă�����
	virtual void Finalize() override {}								//�I�������͎������Ă����Ȃ��Ă�����
	virtual void Update(LPDIRECT3DDEVICE9 lpdev) override {}		//�X�V�����͕K���p����Ŏ�������
	virtual void Draw(LPDIRECT3DDEVICE9 lpdev) override {}			//�`�揈���͕K���p����Ŏ�������
};


#endif