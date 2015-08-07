/**
*@file	Connect.cpp
*@author	亀田
*@brief	通信のテストクラス
*/

#include "Connect.h"


//	初期化
bool Connect::Init()
{
	
	int result = 0;
	result = WSAStartup( MAKEWORD(2,0), &m_wsaData );	///< Winsockの初期化

	if( result != 0 )
	{
		switch(result)
		{
		case WSASYSNOTREADY:///<	ネットワークサブシステムがネットワークへの接続を準備できていない
			printf("WSASYSNOTREADY\n");
			break;

		case WSAVERNOTSUPPORTED:///<	要求されたwinsockのバージョンがサポートされていない
			printf("WSAVERNOTSUPPORTED\n");
			break;

		case WSAEINPROGRESS:///<	ブロッキング操作の実行中であるか、またはサービスプロバイダがコールバック関数を処理している
			printf("WSAEINPROGRESS\n");
			break;

		case WSAEPROCLIM:	///<	winsockが処理できる最大プロセス数に達した
			printf("WSAEPROCLIM\n");
			break;

		case WSAEFAULT:		///<	第二引数であるlpWSAData は有効なポインタではない
			printf("WSAEFAULT\n");
			break;
		}
		return false;
	}
	
	MakeSocket();

	SettingSocket();

	return true;
}

//	ソケット生成
bool Connect::MakeSocket()
{
	m_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		printf("error : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

//	ルーチン処理
void Connect::Control()
{
	EndConnect();
}

//	通信終了
void Connect::EndConnect()
{
	WSACleanup();
}