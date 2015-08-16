#include "SceneManage.h"
#include "graphic.h"


// •`‰æŒãˆ—
void EndRender ();

//----------------------------------------------------

//	•`‰æ‚ÌŠÇ—
//	ˆø”F3Dƒ‚ƒfƒ‹‚ðˆµ‚¤Žž‚Ítrue‚É
void CSceneManager::ViewManage ( bool b3dView )
{
	
	if ( b3dView == true )
	{
		RenderManage();
	}
	DrawManage( b3dView );
}

//	ƒŒƒ“ƒ_ƒŠƒ“ƒOŠÇ—
void CSceneManager::RenderManage ( )
{
	m_pRenderManager->BeginRender();
	
	m_sceneObj -> Render();

	EndRender();
}

//	•`‰æŠÇ—
void CSceneManager::DrawManage ( bool _b3dView )
{
	m_pDrawManager->BeginDraw( _b3dView );

	m_sceneObj -> Draw();

	EndRender();
}


