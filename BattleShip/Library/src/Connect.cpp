/**
*@file	Connect.cpp
*@author	亀田
*@brief	通信のテストクラス
*/

#include "Connect.h"


//	初期化
bool Connect::Init()
{
	//	通信の必要なデータを外部ファイルからセット
	ReadTableData(_CONNECTDATA_PASS_, CONNECT_INFO_MAX, 1);
	
	m_ownSock = NULL;
	m_partnersSock = NULL;
	
	int result = 0;
	result = WSAStartup( MAKEWORD(2,0), &m_wsaData );	///< Winsockの初期化

	if ( result != 0 )
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

	if ( !SettingSocket() )
		return false;

	return true;
}

//	外部ファイルの情報をセット
void Connect::SetTable( char* _p, int _iColumn, int _iLine )
{
	
	switch( _iColumn )
	{
	case SOCK_TYPE:
		if ( memcmp( _p, "Server", 6) == 0 ){
			m_sockType = false;
		}else if ( memcmp( _p, "Client",6) == 0 ){
			m_sockType = true;
		}
		break;
	case DOMAIN_STR:
		if ( m_sockType ){	///<	ドメイン名が必要なのはクライアント側だけなので
			if ( memcmp( _p, "localhost", 9) == 0 ){
				m_domainStr = "127.0.0.1";
			}else{
				m_domainStr = _p;
			}
		}
		break;
	case PORTS_NUM:
		m_ports = atoi(_p);

		break;
	}
}

//	ソケット生成
bool Connect::MakeSocket()
{
	//	ソケットの生成
	m_ownSock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( m_ownSock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Connect::SettingSocket()
{
	// fd_setの初期化します
	FD_ZERO(&m_readfds);

	if ( m_sockType )
	{
		// 接続先指定用構造体の準備
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(m_ports);	///<	ポート番号
		m_addr.sin_addr.S_un.S_addr = inet_addr( m_domainStr.c_str() );
		//	m_domainStrがIPアドレスが入っていなかった場合
		if ( m_addr.sin_addr.S_un.S_addr == 0xffffffff )
		{
			//	ドメイン名が入っている可能性があるので、IPアドレスに変換する。
			struct hostent* host = gethostbyname( (char*)m_domainStr.c_str() );
			if ( host == NULL )
			{
				return false;
			}
			m_addr.sin_addr.S_un.S_addr = *(unsigned int*)host->h_addr_list[0];
		}
	}
	else
	{
		// ソケットの設定
		//	アドレスとポート番号を決めてソケットに情報の紐付けを行う
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(m_ports);
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
	if ( m_sockType ){
		// サーバーに接続
		if (connect(m_ownSock, (struct sockaddr *)&m_addr, sizeof(m_addr)))
		{
			puts("connect に失敗しました");
			return false;
		}
		// selectで待つ読み込みソケットとしてm_ownSockを登録します
		FD_SET(m_ownSock, &m_readfds);
		
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
		// selectで待つ読み込みソケットとしてm_partnersSockを登録します
		FD_SET(m_partnersSock, &m_readfds);
	}
	
	return true;
}

//	受信メソッド
bool Connect::Receive( char *_buf, int _bufSize )
{
	m_selectResult = 0;
	m_tv.tv_sec = _RECV_TIMEOUT_SECOND_;	
	m_tv.tv_usec = 0;

	// 読み込み用fd_setの初期化
	// selectが毎回内容を上書きしてしまうので、毎回初期化します
	memcpy(&m_fds, &m_readfds, sizeof(fd_set));

	// fdsに設定されたソケットが読み込み可能になるまで待ちます
	m_selectResult = select( 0, &m_fds, NULL, NULL, &m_tv );
	// タイムアウトの場合にselectは0を返します
	if ( m_selectResult == 0 )
	{
		// ループから抜けます
		return false;
	}
	//	念のためバッファーの初期化
	memset(_buf,0,_bufSize);
	int iRecvResult = 0;
	if ( m_sockType )
	{
		// 自身のソケットにに読み込み可能データがある場合
		if ( FD_ISSET( m_ownSock, &m_fds) )
		{
			iRecvResult = recv(m_ownSock, _buf, _bufSize, 0 );
		}
	}
	else 
	{
		// 相手のソケットにに読み込み可能データがある場合
		if ( FD_ISSET( m_partnersSock, &m_fds) ) 
		{
			iRecvResult = recv(m_partnersSock, _buf, _bufSize, 0 );
		}
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
	if ( m_sockType ){
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
	if ( m_partnersSock != NULL )
		closesocket(m_partnersSock);
	
	closesocket(m_ownSock);
	WSACleanup();
}