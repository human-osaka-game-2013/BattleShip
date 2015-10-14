/**
*@file	Connect.cpp
*@author	亀田
*@brief	通信のテストクラス
*/

#include "Connect.h"


//	初期化
bool Connect::Init( bool _bSockType )
{
	m_sockType = _bSockType;
	
	m_ownSock = NULL;
	m_partnersSock = NULL;
	
	int result = 0;
	result = WSAStartup( MAKEWORD(2,0), &m_wsaData );	///< Winsockの初期化

	if( result != 0 )
	{
		switch(result)
		{
		case WSASYSNOTREADY:///<	ネットワークサブシステムがネットワークへの接続を準備できていない
			MessageBoxA(0,"WSASYSNOTREADY\n",NULL,MB_OK);
			break;

		case WSAVERNOTSUPPORTED:///<	要求されたwinsockのバージョンがサポートされていない
			MessageBoxA(0,"WSAVERNOTSUPPORTED\n",NULL,MB_OK);
			break;

		case WSAEINPROGRESS:///<	ブロッキング操作の実行中であるか、またはサービスプロバイダがコールバック関数を処理している
			MessageBoxA(0,"WSAEINPROGRESS\n",NULL,MB_OK);
			break;

		case WSAEPROCLIM:	///<	winsockが処理できる最大プロセス数に達した
			MessageBoxA(0,"WSAEPROCLIM\n",NULL,MB_OK);
			break;

		case WSAEFAULT:		///<	第二引数であるlpWSAData は有効なポインタではない
			MessageBoxA(0,"WSAEFAULT\n",NULL,MB_OK);
			break;
		}
		return false;
	}
	
	MakeSocket();	///<	ソケット作成

	return true;
}

//	ソケット生成
bool Connect::MakeSocket()
{
	//	ソケットの生成
	m_ownSock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_ownSock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Connect::SettingSocket( int _ports, char* _domainStr )
{
	if( m_sockType ){
		// 接続先指定用構造体の準備
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(_ports);	///<	ポート番号
		m_addr.sin_addr.S_un.S_addr = inet_addr( _domainStr );
	}
	else
	{
		// ソケットの設定
		//	アドレスとポート番号を決めてソケットに情報の紐付けを行う
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(_ports);
		m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
		//	bind関数でソケットをIPアドレスとポート番号と組み合わせをして、
		//	インターフェースの協力関係を作る。
		bind( m_ownSock, (struct sockaddr *)&m_addr, sizeof(m_addr));
		
	}
	return true;
}


//	受信メソッド
bool Connect::Connection()
{
	if( m_sockType ){
		// サーバーに接続
		if (connect(m_ownSock, (struct sockaddr *)&m_addr, sizeof(m_addr)))
		{
			puts("connect に失敗しました");
			return false;
		}
		
	}
	else{
		// TCPクライアントからの接続要求を待てる状態にする
		listen( m_ownSock, 5);
		int len = sizeof( m_client );
		//	要求があったらaccept関数で要求を受け取ったという合図をおくり
		//	Client側のソケットデータをもらう
		m_partnersSock = accept( m_ownSock, (struct sockaddr *)&m_client, &len);
		if (m_partnersSock == INVALID_SOCKET)
		{ 
			DebugMsgBox("accept : %d\n", WSAGetLastError());
			return false;
		}
	}
	
	return true;
}

//	受信メソッド
bool Connect::Receive( char *_buf, int _bufSize )
{
	//	念のためバッファーの初期化
	memset(_buf,0,_bufSize);
	int iRecvResult = 0;
	if( m_sockType ){
		iRecvResult = recv(m_ownSock, _buf, _bufSize, 0 );
	}
	else {
		iRecvResult = recv(m_partnersSock, _buf, _bufSize, 0 );
	}

	if (iRecvResult < 0)
	{   
		puts("recv に失敗しました");
	    return false;
	}
	return true;
}

//	送信メソッド
bool Connect::Send( char *_buf, int _bufSize )
{
	int iSendResult = 0;
	if( m_sockType ){
		iSendResult = send( m_ownSock, (const char*)_buf, _bufSize, 0);
	}
	else{
		iSendResult = send( m_partnersSock, (const char*)_buf, _bufSize, 0);
	}

	if (iSendResult < 0)
	{  
		puts("send に失敗しました");
	    return false;
	}
	return true;
}



//	通信終了
void Connect::EndConnect()
{
	if( m_partnersSock != NULL )
		closesocket(m_partnersSock);
	
	closesocket(m_ownSock);
	WSACleanup();
}