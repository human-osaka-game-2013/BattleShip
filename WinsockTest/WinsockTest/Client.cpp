/**
*@file	Client.cpp
*@author	�T�c
*@brief	�N���C�A���g���ʐM�N���X
*/

#include "Client.h"

bool Client::SettingSocket()
{
	// �ڑ���w��p�\���̂̏���
	m_server.sin_family = AF_INET;
	m_server.sin_port = htons(12345);
	m_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	return true;
}


void Client::ConnectToServer()
{
	//	�T�[�o�ɐڑ�
	connect( *GetSocket(), (struct sockaddr *)&m_server, sizeof(m_server));
}

bool Client::Receive()
{
	memset(m_buf, 0, sizeof(m_buf));
	//	�T�[�o����̃f�[�^��M
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