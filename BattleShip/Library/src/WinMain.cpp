/**
*@file	WinMain.cpp
*@author	亀田
*@brief	WinMain関数
*/

#include "SceneManage.h"
#include "Proc.h"
#include "Window.h"
#include "device.h"
#include "AllInput.h"

#include "DebugNew.h"

//----------------------------------------------------------------------
//
//	メインルーチン
//
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR IpCmdLine, int nCmdShow )
{
	HWND	hWnd;

	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(152);
	
	MSG msg;
	
	CreateWindowProcess ( hInstance, &hWnd );

	CDevice deviceObj( &hWnd );	///<デバイス管理クラスオブジェクト

	if( FAILED (deviceObj.InitDevice())) return 0;	///<デバイス管理クラスの初期化

	// サウンドの初期化
	//InitXAudio2();

	//	シーン管理オブジェクトの生成
	CSceneManager* pSceneManage = new CSceneManager( CSceneManager::SCENE_TITLE, &deviceObj, false );

	srand(( unsigned )time( NULL ));

	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	ZeroMemory (&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);

		if ( PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}

		else
		{
			SyncNow = timeGetTime();

			if (SyncNow - SyncOld >= 1000 / 60)
			{
				//	ゲームメイン関数
				pSceneManage -> GameMain ();

				SyncOld = SyncNow;

				
			}
		}
	}

	timeEndPeriod(1);

	
	//ReleaseXAudio2();


	if ( false == pSceneManage -> DeleteSceneObj() )	return 0;

	delete pSceneManage;

	return (int)msg.wParam;
}
