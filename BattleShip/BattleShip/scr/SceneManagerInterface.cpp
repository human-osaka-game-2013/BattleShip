#include "SceneManage.h"
#include "GameScene.h"

//	シーン管理
void CSceneManager::Manage ()
{
	static int	iBeforeScene = SCENE_NONE;	//	前のシーン。最初だけNONEで初期化

	//	シーン変更フラグが立っているので、CSceneを継承しているクラスからIDを引き抜く
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	現在のシーンを切り替える
	
	if ( iBeforeScene != iCurrentScene )
	{
		switch ( iCurrentScene )
		{
		case SCENE_LOGO:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new CLogo( iCurrentScene );
			
			break;

		case SCENE_TITLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new CTitle( iCurrentScene );

			break;

		//case SELECT:
		//	CLASS_DELETE( m_sceneObj );
		//	m_sceneObj = new CSelect( iCurrentScene );
		//	
		//	break;

		case SCENE_BATTLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new GameScene();
		
			break;

		//case RESULT:
		//	CLASS_DELETE( m_sceneObj );
		//	m_sceneObj = new CResult( iCurrentScene );
		//	
		//	break;
		}
		
		UpdateChangeFlag ( true );
	}
	iBeforeScene = iCurrentScene;
}

//	シーンオブジェクトの解放
bool CSceneManager::DeleteSceneObj()
{
	CLASS_DELETE( m_sceneObj );
	CLASS_DELETE( m_pRenderManager );
	CLASS_DELETE( m_pDrawManager );
	CLASS_DELETE( m_pKey );
	CLASS_DELETE( m_pMouse );
	CLASS_DELETE( m_pXInput );
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
