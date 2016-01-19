#include <stdio.h>
#include "SceneManage.h"

//---------------------------------------------------
//	プロトタイプ宣言
//---------------------------------------------------


//	シーンクラスのルーチンの制御
void CSceneManager::SceneRoutingManage ()
{
	int _SceneIDTemp = SCENE_NONE;

	if ( GetChangeSceneFlag() == true )
	{
		m_sceneObj -> Init ();
		UpdateChangeFlag ( false );	//	シーン変更も終わり、初期化も通ったから
		_SceneIDTemp = GetCurrentScene();
	}
	m_sceneObj->CountTimeInScene();	//	シーン内時間のカウント
	int iCntResult = m_sceneObj -> Control ();
	//	各シーンのControl関数からの返り値が1だった場合にシーンの切り替えを行う
	switch ( iCntResult )
	{
	case 0:

		break;
	case 1:
		if ( GetCurrentScene()+1 < SCENE_MAX  )
		{
			iCurrentScene++;
		}
		else
		{
			iCurrentScene = SCENE_NONE+1;
		}
		m_sceneObj->SetSceneID( iCurrentScene );//	変更するシーンIDを入れる	
		UpdateChangeFlag(true);	//	変更フラグを立てる
		break;
	}
}