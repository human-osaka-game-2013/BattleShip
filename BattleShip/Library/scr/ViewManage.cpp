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
	DrawManage( );
}

//	ƒŒƒ“ƒ_ƒŠƒ“ƒOŠÇ—
void CSceneManager::RenderManage ( )
{
	
	
	m_sceneObj -> Render();

	EndRender();
}

//	•`‰æŠÇ—
void CSceneManager::DrawManage (  )
{

	m_sceneObj -> Draw();

	EndRender();
}


