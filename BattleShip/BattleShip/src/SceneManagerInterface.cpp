#include "GameScene.h"
#include "TitleScene.h"
#include "SceneManage.h"

//	シーン管理
void CSceneManager::Manage ()
{
	static int	iBeforeScene = SCENE_NONE;	//	前のシーン。最初だけNONEで初期化

	m_pMouse->AllButtonCheck();	///<マウスボタンの状態更新
	m_pMouse->CursorSet( m_pDevice->GetWindowHandle() );	///<マウス座標更新

	//	シーン変更フラグが立っているので、CSceneを継承しているクラスからIDを引き抜く
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	現在のシーンを切り替える
	
	if ( iBeforeScene != iCurrentScene )
	{
		if( iBeforeScene != SCENE_NONE )
			m_sceneObj->Free();
		switch ( iCurrentScene )
		{
		case SCENE_BATTLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new GameScene( iCurrentScene, m_pRenderManager, m_pDrawManager, m_pKey, m_pMouse );
			break;

		case SCENE_TITLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new TitleScene( iCurrentScene, m_pRenderManager, m_pDrawManager, m_pKey, m_pMouse );
			
			break;
		}
		
		UpdateChangeFlag ( true );
	}
	iBeforeScene = iCurrentScene;
}

//	シーンオブジェクトの解放
bool CSceneManager::DeleteSceneObj()
{
	m_sceneObj->Free();
	if( m_pRenderManager != NULL )
		CLASS_DELETE( m_pRenderManager );
	CLASS_DELETE( m_pDrawManager );
	CLASS_DELETE( m_pKey );
	CLASS_DELETE( m_pMouse );
	CLASS_DELETE( m_pXInput );
	CLASS_DELETE( m_sceneObj );
	if( m_sceneObj != NULL )
		return false;
	if( m_pRenderManager != NULL )
		return false;
	if( m_pDrawManager != NULL )
		return false;
	if( m_pKey != NULL )
		return false;
	if( m_pMouse != NULL )
		return false;
	if( m_pXInput != NULL )
		return false;

	return true;
}
