/**
*@file	Server.cpp
*@author	亀田
*@brief	サーバー側通信クラス
*/

#include "Server.h"


void Server::SettingSocket()
{
	//	ソケットの設定
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(12345);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind( *GetSocket(), (struct sockaddr *)&m_addr, sizeof( m_addr ));
}


bool Server::KeepListen()
{
	//	TCPクライアントからの接続要求を待てる状態にする
	listen( *GetSocket(), 5);

	//	TCPクライアントからの接続要求を受け付ける
	m_len = sizeof(m_client);
	m_sock0 = accept( *GetSocket(), (struct sockaddr *)&m_client, &m_len );

	if( *GetSocket() == INVALID_SOCKET ) 
	{
		printf("error : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

void Server::Send()
{
	send(m_sock0, "HELLO", 5, 0);
}

void Server::EndConnect()
{
	// TCPセッションの終了
	closesocket(m_sock0);
	// winsock2の終了処理
	WSACleanup();
}