#include "SceneManage.h"
#include "GameScene.h"

//	�V�[���Ǘ�
void CSceneManager::Manage ()
{
	static int	iBeforeScene = SCENE_NONE;	//	�O�̃V�[���B�ŏ�����NONE�ŏ�����

	//	�V�[���ύX�t���O�������Ă���̂ŁACScene���p�����Ă���N���X����ID����������
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	���݂̃V�[����؂�ւ���
	
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

//	�V�[���I�u�W�F�N�g�̉��
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
