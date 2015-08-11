/**
*@file	Server.cpp
*@author	亀田
*@brief	サーバー側通信クラス
*/

#include "Server.h"

//#define _TEST_HTTP_

bool Server::SettingSocket()
{
	m_reuseFlag = false;
	//	ソケットの設定
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(12345);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//	SO_REUSEADDRの有効処理
	setsockopt( *GetSocket(),
		SOL_SOCKET, SO_REUSEADDR, (const char *)&m_reuseFlag, sizeof( m_reuseFlag ) );

	//	アドレス、ポートへ結びつけ
	if( bind( *GetSocket(), (struct sockaddr *)&m_addr, sizeof( m_addr )) != 0 )
	{
		DebugMsgBox("bind：%d\n", WSAGetLastError());
		return false;
	}
	return true;
}


bool Server::KeepListen()
{
	//	TCPクライアントからの接続要求を待てる状態にする
	if( listen( *GetSocket(), 5) != 0 )
	{
		DebugMsgBox("listen：%d\n", WSAGetLastError());	///<接続待ちが失敗
		return false;
	}
#ifdef _TEST_HTTP_
	//----HTTPサーバサンプルテスト用
	//	応答用HTTPメッセージ作成
	memset( m_buf, 0, sizeof( m_buf ) );
	_snprintf( m_buf, sizeof( m_buf ),
		"HTTP/1.0 200 OK\r\n"
		"Content-Length: 20\r\n"
		"Content-Type: text/html\r\n"
		"\r\n"
		"HELLO\r\n");
	//----
#endif
	while(1)	///	複数回クライアント側からの接続を受け付ける
	{
		//	TCPクライアントからの接続要求を受け付ける
		m_len = sizeof(m_client);
		m_sock0 = accept( *GetSocket(), (struct sockaddr *)&m_client, &m_len );

		DebugMsgBox("accepted connection from %s, port=%d\n",
          inet_ntoa(m_client.sin_addr), ntohs(m_client.sin_port));

		if( m_sock0 == INVALID_SOCKET ) 
		{
			DebugMsgBox("accept : %d\n", WSAGetLastError());	///<	接続失敗
			return false;
		}
		Send( &m_sock0, m_buf );

		// TCPセッションの終了
		closesocket(m_sock0); 
	}
	return true;
}


void Server::EndConnect()
{
	// winsock2の終了処理
	WSACleanup();
}