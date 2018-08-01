//*****************************************************************************
//!	@file	SceneManager.h
//!	@brief	シーン管理クラス
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
	if (mNextScene != eScene_None) {    //次のシーンがセットされていたら
		mScene->Finalize();//現在のシーンの終了処理を実行
		delete mScene;
		//free(mScene);
		switch (mNextScene) {       //シーンによって処理を分岐
		case eScene_Title:        //次の画面がメニューなら
			mScene = (SceneBase*) new TitleScene(this);   //タイトル画面のインスタンスを生成する
			//mScene = (SceneBase*)malloc(sizeof(TitleScene(this)));
			break;//以下略
		case eScene_Stage0:
			mScene = (SceneBase*) new Stage0Scene(this);   
			//mScene = (SceneBase*)malloc(sizeof(GameScene(this)));
			break;//以下略
		}
		mNextScene = eScene_None;    //次のシーン情報をクリア
		mScene->Initialize(lpdev);    //シーンを初期化
	}

	mScene->Update(lpdev); //シーンの更新
}

void SceneManager::Draw(LPDIRECT3DDEVICE9 lpdev)
{
	mScene->Draw(lpdev);
}

void SceneManager::ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;		//次のシーンをセットする
}

//*****************************************************************************
//	End of file.
//*****************************************************************************