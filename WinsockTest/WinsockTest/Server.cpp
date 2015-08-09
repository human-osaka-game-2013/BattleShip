/**
*@file	Server.cpp
*@author	�T�c
*@brief	�T�[�o�[���ʐM�N���X
*/

#include "Server.h"


bool Server::SettingSocket()
{
	//	�\�P�b�g�̐ݒ�
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(12345);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	//	�A�h���X�A�|�[�g�֌��т�
	if( bind( *GetSocket(), (struct sockaddr *)&m_addr, sizeof( m_addr )) != 0 )
	{
		printf("bind�F%d\n", WSAGetLastError());
		return false;
	}
	return true;
}


bool Server::KeepListen()
{
	//	TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	if( listen( *GetSocket(), 5) != 0 )
	{
		printf("listen�F%d\n", WSAGetLastError());	///<�ڑ��҂������s
		return false;
	}

	while(1)	///	������N���C�A���g������̐ڑ����󂯕t����
	{
		//	TCP�N���C�A���g����̐ڑ��v�����󂯕t����
		m_len = sizeof(m_client);
		m_sock0 = accept( *GetSocket(), (struct sockaddr *)&m_client, &m_len );

		printf("accepted connection from %s, port=%d\n",
          inet_ntoa(m_client.sin_addr), ntohs(m_client.sin_port));

		if( m_sock0 == INVALID_SOCKET ) 
		{
			printf("accept : %d\n", WSAGetLastError());	///<	�ڑ����s
			return false;
		}
		Send();

		// TCP�Z�b�V�����̏I��
		closesocket(m_sock0);
	}
	return true;
}

bool Server::Send()
{
	int n = send(m_sock0, "HELLO", 5, 0);
	if( n < 1 )
	{
		printf("send�F%d\n", WSAGetLastError() );	///<	���M���s
		return false;
	}
	return true;
}

void Server::EndConnect()
{
	// winsock2�̏I������
	WSACleanup();
}