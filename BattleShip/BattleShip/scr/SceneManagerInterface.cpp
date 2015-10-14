#include "SceneManage.h"
#include "GameScene.h"

//	�V�[���Ǘ�
void CSceneManager::Manage ()
{
	static int	iBeforeScene = SCENE_NONE;	//	�O�̃V�[���B�ŏ�����NONE�ŏ�����

	m_pMouse->AllButtonCheck();	///<�}�E�X�{�^���̏�ԍX�V
	m_pMouse->CursorSet( m_pDevice->GetWindowHandle() );	///<�}�E�X���W�X�V

	//	�V�[���ύX�t���O�������Ă���̂ŁACScene���p�����Ă���N���X����ID����������
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	���݂̃V�[����؂�ւ���
	
	if ( iBeforeScene != iCurrentScene )
	{
		switch ( iCurrentScene )
		{
		case SCENE_BATTLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new GameScene( iCurrentScene, 0, 
										m_pRenderManager, m_pDrawManager, m_pKey, m_pMouse,
										m_pDevice->GetConnectDevice());
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
