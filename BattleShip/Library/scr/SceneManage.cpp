/**
*@file	SceneManager.cpp
*@author	亀田
*@brief	シーン管理
*/

#include "SceneManage.h"

//	コンストラクタ
CSceneManager::CSceneManager(  int _scene , CDevice* const _pDevice, bool _bRenderType  ) : 
	m_sceneObj( NULL ), iCurrentScene( _scene ), bChangeSceneFlag( false ),
		m_pDevice( _pDevice), m_bRenderType(_bRenderType)
{
	//	3D描画の管理オブジェクトの生成
	m_pRenderManager = new CRenderManager( m_pDevice->Getd3Device(), m_pDevice->GetMouseDevice());

	//	2D描画の管理オブジェクトの生成
	m_pDrawManager = new CDrawManager( m_pDevice->Getd3Device() );

	//	キー管理クラス生成
	m_pKey = new CKey( m_pDevice->GetKeyDevice() );

	//	マウス管理クラス生成
	m_pMouse = new CMouse( m_pDevice->GetMouseDevice() );

	m_pXInput = new CXInput();
}



// 描画後処理
void CSceneManager::EndRender ()
{
	
	// 描画の終了
	m_pDevice->Getd3Device() -> EndScene();

	// 表示
	m_pDevice->Getd3Device() -> Present ( NULL, NULL, NULL, NULL );
}

/*
	デストラクタ
*/
CSceneManager::~CSceneManager()
{
	if( !DeleteSceneObj() )	{

	}
}

