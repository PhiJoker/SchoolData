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
	eScene_Title,	//	���j���[���
	eScene_Stage0,	//	Stage0���
	eScene_Config,	//	�ݒ���

	eScene_None,    //	����
} eScene;

//	�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	ISceneChanger() {}
	virtual ~ISceneChanger() = 0 {}
	virtual void ChangeScene(eScene NextScene) = 0 {}//	�w��V�[���ɕύX����
};

#endif