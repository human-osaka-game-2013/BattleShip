/**
*@file	Client.cpp
*@author	亀田
*@brief	クライアント側通信クラス
*/

#include "Client.h"

bool Client::SettingSocket()
{
	// 接続先指定用構造体の準備
	m_server.sin_family = AF_INET;
	m_server.sin_port = htons(12345);
	m_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	return true;
}


void Client::ConnectToServer()
{
	//	サーバに接続
	connect( *GetSocket(), (struct sockaddr *)&m_server, sizeof(m_server));
}

bool Client::Receive()
{
	memset(m_buf, 0, sizeof(m_buf));
	//	サーバからのデータ受信
	int n = recv( *GetSocket(), m_buf, sizeof(m_buf), 0 );

	if( n == NULL )
	{
		return false;
	}
	printf("%d, %s\n", n, m_buf);
	return true;
}

void Client::EndConnect()
{

}