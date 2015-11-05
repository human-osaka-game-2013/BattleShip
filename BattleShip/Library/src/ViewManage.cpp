#include "SceneManage.h"
#include "graphic.h"


// �`��㏈��
void EndRender ();

//----------------------------------------------------

//	�`��̊Ǘ�
//	�����F3D���f������������true��
void CSceneManager::ViewManage ( bool b3dView )
{
	
	if ( b3dView == true )
	{
		RenderManage();
	}
	DrawManage( b3dView );
}

//	�����_�����O�Ǘ�
void CSceneManager::RenderManage ( )
{
	m_pRenderManager->BeginRender();
	
	m_sceneObj -> Render();

	EndRender();
}

//	�`��Ǘ�
void CSceneManager::DrawManage ( bool _b3dView )
{
	m_pDrawManager->BeginDraw( _b3dView );

	m_sceneObj -> Draw();

	EndRender();
}


