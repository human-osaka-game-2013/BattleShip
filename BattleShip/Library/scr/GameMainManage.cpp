#include <stdio.h>
#include "SceneManage.h"

//---------------------------------------------------
//	プロトタイプ宣言
//---------------------------------------------------


//	シーンクラスのルーチンの制御
void CSceneManager::SceneRoutingManage ()
{
	int _SceneIDTemp = SCENE_NONE;

	if ( true == GetChangeSceneFlag() )
	{
		m_sceneObj -> Init ();
		UpdateChangeFlag ( false );	//	シーン変更も終わり、初期化も通ったから
		_SceneIDTemp = GetCurrentScene();
	}

	int iCntResult = m_sceneObj -> Control ();
	switch( iCntResult )
	{
	case 0:

		break;
	case 1:
		if( GetCurrentScene()+1 < SCENE_MAX  )
		{
			iCurrentScene++;
		}
		else
		{
			iCurrentScene = SCENE_NONE+1;
		}
		UpdateChangeFlag(true);	//	変更フラグを立てる
		break;
	}
}