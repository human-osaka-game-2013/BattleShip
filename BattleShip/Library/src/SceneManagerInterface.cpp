#include "GameScene.h"
#include "SceneManage.h"
#include "TitleScene.h"

//	�V�[���Ǘ�
void CSceneManager::Manage ()
{
	static int	iBeforeScene = SCENE_NONE;	//	�O�̃V�[���B�ŏ�����NONE�ŏ�����

	m_pMouse->AllButtonCheck();	///<�}�E�X�{�^���̏�ԍX�V
	m_pMouse->CursorSet( m_pDevice->GetWindowHandle() );	///<�}�E�X���W�X�V

	//	�V�[���ύX�t���O�������Ă���̂ŁACScene���p�����Ă���N���X����ID����������
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	���݂̃V�[����؂�ւ���
	
	//	�V�[�����ς���Ă�����
	if ( iBeforeScene != iCurrentScene )
	{
		//	�{���ɃV�[���̐؂�ւ��ł��邩�im_sceneObj�ɂ܂��f�[�^�������Ă��Ȃ������ꍇ���l���j
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
		//	�V�[����ς����̂ŏ�������������K�v������B
		UpdateChangeFlag ( true );
		//	�����őS�Ă̍Đ����Ă��鉹����O�̂��߃X�g�b�v
		m_pAudio->SoundAllStop();
	}
	iBeforeScene = iCurrentScene;
}

//	�V�[���I�u�W�F�N�g�̉��
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
