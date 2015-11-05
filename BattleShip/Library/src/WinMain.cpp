/**
*@file	WinMain.cpp
*@author	�T�c
*@brief	WinMain�֐�
*/

#include "SceneManage.h"
#include "Proc.h"
#include "Window.h"
#include "device.h"
#include "AllInput.h"

#include "DebugNew.h"

//----------------------------------------------------------------------
//
//	���C�����[�`��
//
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR IpCmdLine, int nCmdShow )
{
	HWND	hWnd;

	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(152);
	
	MSG msg;
	
	CreateWindowProcess ( hInstance, &hWnd );

	CDevice deviceObj( &hWnd );	///<�f�o�C�X�Ǘ��N���X�I�u�W�F�N�g

	if( FAILED (deviceObj.InitDevice())) return 0;	///<�f�o�C�X�Ǘ��N���X�̏�����

	// �T�E���h�̏�����
	//InitXAudio2();

	//	�V�[���Ǘ��I�u�W�F�N�g�̐���
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
				//	�Q�[�����C���֐�
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
