#include "graphic.h"
#include "SceneManage.h"
#include "AllInput.h"

//	ƒQ[ƒ€ƒƒCƒ“ŠÖ”
int CSceneManager::GameMain ()
{
	Manage();

	SceneRoutingManage();

	ViewManage( true );

	return 0;
}