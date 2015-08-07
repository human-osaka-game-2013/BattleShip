/**
*@file	Server.cpp
*@author	�T�c
*@brief	�T�[�o�[���ʐM�N���X
*/

#include "Server.h"


void Server::SettingSocket()
{
	//	�\�P�b�g�̐ݒ�
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(12345);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind( *GetSocket(), (struct sockaddr *)&m_addr, sizeof( m_addr ));
}


bool Server::KeepListen()
{
	//	TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	listen( *GetSocket(), 5);

	//	TCP�N���C�A���g����̐ڑ��v�����󂯕t����
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
	// TCP�Z�b�V�����̏I��
	closesocket(m_sock0);
	// winsock2�̏I������
	WSACleanup();
}