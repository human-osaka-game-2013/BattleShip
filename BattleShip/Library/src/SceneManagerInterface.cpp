#include "GameScene.h"
#include "SceneManage.h"
#include "TitleScene.h"

//	シーン管理
void CSceneManager::Manage ()
{
	static int	iBeforeScene = SCENE_NONE;	//	前のシーン。最初だけNONEで初期化

	m_pMouse->AllButtonCheck();	///<マウスボタンの状態更新
	m_pMouse->CursorSet( m_pDevice->GetWindowHandle() );	///<マウス座標更新

	//	シーン変更フラグが立っているので、CSceneを継承しているクラスからIDを引き抜く
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	現在のシーンを切り替える
	
	//	シーンが変わっていたら
	if ( iBeforeScene != iCurrentScene )
	{
		//	本当にシーンの切り替わりであるか（m_sceneObjにまだデータが入っていなかった場合を考慮）
		if( iBeforeScene != SCENE_NONE )
		{
			CLASS_DELETE( m_sceneObj );
		}
		switch ( iCurrentScene )
		{
		case SCENE_BATTLE:
			m_sceneObj = new GameScene( iCurrentScene, m_pRenderManager, m_pDrawManager, m_pKey, m_pMouse, m_pAudio );
			break;

		case SCENE_TITLE:
			m_sceneObj = new TitleScene( iCurrentScene, m_pRenderManager, m_pDrawManager, m_pKey, m_pMouse, m_pAudio );
			
			break;
		}
		//	シーンを変えたので初期化をさせる必要がある。
		UpdateChangeFlag ( true );
		//	ここで全ての再生している音声を念のためストップ
		m_pAudio->SoundAllStop();
	}
	iBeforeScene = iCurrentScene;
}

//	シーンオブジェクトの解放
bool CSceneManager::DeleteSceneObj()
{

	if( m_pRenderManager != NULL )
		CLASS_DELETE( m_pRenderManager );
	CLASS_DELETE( m_pDrawManager );
	CLASS_DELETE( m_pKey );
	CLASS_DELETE( m_pMouse );
	CLASS_DELETE( m_pXInput );
	CLASS_DELETE( m_sceneObj );
	CLASS_DELETE( m_pAudio );

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
	if( m_pAudio != NULL )
		return false;
	return true;
}
