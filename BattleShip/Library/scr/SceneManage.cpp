/**
*@file	SceneManager.cpp
*@author	�T�c
*@brief	�V�[���Ǘ�
*/

#include "SceneManage.h"

//	�R���X�g���N�^
CSceneManager::CSceneManager(  int _scene , CDevice* const _pDevice, bool _bRenderType  ) : 
	m_sceneObj( NULL ), iCurrentScene( _scene ), bChangeSceneFlag( false ),
		m_pDevice( _pDevice), m_bRenderType(_bRenderType)
{
	//	3D�`��̊Ǘ��I�u�W�F�N�g�̐���
	m_pRenderManager = new CRenderManager( m_pDevice->Getd3Device(), m_pDevice->GetMouseDevice());

	//	2D�`��̊Ǘ��I�u�W�F�N�g�̐���
	m_pDrawManager = new CDrawManager( m_pDevice->Getd3Device() );

	//	�L�[�Ǘ��N���X����
	m_pKey = new CKey( m_pDevice->GetKeyDevice() );

	//	�}�E�X�Ǘ��N���X����
	m_pMouse = new CMouse( m_pDevice->GetMouseDevice() );

	m_pXInput = new CXInput();
}



// �`��㏈��
void CSceneManager::EndRender ()
{
	
	// �`��̏I��
	m_pDevice->Getd3Device() -> EndScene();

	// �\��
	m_pDevice->Getd3Device() -> Present ( NULL, NULL, NULL, NULL );
}

/*
	�f�X�g���N�^
*/
CSceneManager::~CSceneManager()
{
	if( !DeleteSceneObj() )	{

	}
}

