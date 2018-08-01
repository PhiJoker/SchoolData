//*****************************************************************************
//!	@file	SceneManager.h
//!	@brief	�V�[���Ǘ��N���X
//!	@note	2018/07/25
//!	@author
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "SceneManager.h"

SceneManager::SceneManager():mNextScene(eScene_None)
{
	//mScene = (SceneBase*)malloc(sizeof(TitleScene));
	//mScene = 
	mScene = (SceneBase*) new TitleScene(this);
}

void SceneManager::Initialize(LPDIRECT3DDEVICE9 lpdev)
{
	mScene->Initialize(lpdev);
}

void SceneManager::Finalize()
{
	mScene->Finalize();
}

void SceneManager::Update(LPDIRECT3DDEVICE9 lpdev)
{
	if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		//free(mScene);
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eScene_Title:        //���̉�ʂ����j���[�Ȃ�
			mScene = (SceneBase*) new TitleScene(this);   //�^�C�g����ʂ̃C���X�^���X�𐶐�����
			//mScene = (SceneBase*)malloc(sizeof(TitleScene(this)));
			break;//�ȉ���
		case eScene_Stage0:
			mScene = (SceneBase*) new Stage0Scene(this);   
			//mScene = (SceneBase*)malloc(sizeof(GameScene(this)));
			break;//�ȉ���
		}
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize(lpdev);    //�V�[����������
	}

	mScene->Update(lpdev); //�V�[���̍X�V
}

void SceneManager::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	mScene->Draw(lpdev);
}

void SceneManager::ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;		//���̃V�[�����Z�b�g����
}

//*****************************************************************************
//	End of file.
//*****************************************************************************