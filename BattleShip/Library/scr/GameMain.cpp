#include "graphic.h"
#include "SceneManage.h"
#include "AllInput.h"

//	�Q�[�����C���֐�
int CSceneManager::GameMain ()
{
	Manage();

	SceneRoutingManage();

	ViewManage( true );

	return 0;
}