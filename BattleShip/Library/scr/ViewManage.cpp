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
	DrawManage( );
}

//	�����_�����O�Ǘ�
void CSceneManager::RenderManage ( )
{
	
	
	m_sceneObj -> Render();

	EndRender();
}

//	�`��Ǘ�
void CSceneManager::DrawManage (  )
{

	m_sceneObj -> Draw();

	EndRender();
}


