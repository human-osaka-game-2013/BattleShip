
#include "SceneInterface.h"
//	コンストラクタ
CScene::CScene( int _id, CRenderManager* const _pRenderManager,
		CDrawManager* const _pDrawManager,
		CKey* const _pKey, CMouse* const _pMouse, Audio* const _pAudio ) 
	: m_sceneID( _id ), m_pRenderManager(_pRenderManager), 
	m_pDrawManager(_pDrawManager), m_pKey(_pKey), m_pMouse(_pMouse), m_pAudio(_pAudio)	
{
	m_sceneTime = 0;	
	m_sceneEndFlag = false;
}
