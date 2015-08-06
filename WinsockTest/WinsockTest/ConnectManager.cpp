/**
*@file	ConnectManager.cpp
*@author	亀田
*@brief	通信のテストクラス
*/

#include "ConnectManager.h"
#include <cstdio>

bool ConnectManager::Init()
{
	
	int result = 0;
	result = WSAStartup( MAKEWORD(2,0), &m_wsaData );

	if( result != 0 )
	{
		switch(result)
		{
		case WSASYSNOTREADY:
			printf("WSASYSNOTREADY\n");
			break;

		case WSAVERNOTSUPPORTED:
			printf("WSAVERNOTSUPPORTED\n");
			break;

		case WSAEINPROGRESS:
			printf("WSAEINPROGRESS\n");
			break;

		case WSAEPROCLIM:
			printf("WSAEPROCLIM\n");
			break;

		case WSAEFAULT:
			printf("WSAEFAULT\n");
			break;
		}
	}


	return true;
}

void ConnectManager::Control()
{
	EndConnect();
}

void ConnectManager::EndConnect()
{
	WSACleanup();
}