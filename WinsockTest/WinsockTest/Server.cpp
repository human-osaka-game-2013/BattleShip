/**
*@file	Server.cpp
*@author	�T�c
*@brief	�T�[�o�[���ʐM�N���X
*/

#include "Server.h"

//#define _TEST_HTTP_

bool Server::SettingSocket()
{
	m_reuseFlag = false;
	//	�\�P�b�g�̐ݒ�
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(12345);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//	SO_REUSEADDR�̗L������
	setsockopt( *GetSocket(),
		SOL_SOCKET, SO_REUSEADDR, (const char *)&m_reuseFlag, sizeof( m_reuseFlag ) );

	//	�A�h���X�A�|�[�g�֌��т�
	if( bind( *GetSocket(), (struct sockaddr *)&m_addr, sizeof( m_addr )) != 0 )
	{
		DebugMsgBox("bind�F%d\n", WSAGetLastError());
		return false;
	}
	return true;
}


bool Server::KeepListen()
{
	//	TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	if( listen( *GetSocket(), 5) != 0 )
	{
		DebugMsgBox("listen�F%d\n", WSAGetLastError());	///<�ڑ��҂������s
		return false;

		
	}
	while(1)	///	������N���C�A���g������̐ڑ����󂯕t����
	{
		memset( m_buf, 0, sizeof( m_buf ) );
		_snprintf( m_buf, sizeof( m_buf ),"Server�����瑗��ꂽ������ł�\n");
		
		//	TCP�N���C�A���g����̐ڑ��v�����󂯕t����
		m_len = sizeof(m_client);
		m_sock0 = accept( *GetSocket(), (struct sockaddr *)&m_client, &m_len );

		printf_s("accepted connection from %s, port=%d\n",
          inet_ntoa(m_client.sin_addr), ntohs(m_client.sin_port));

		if( m_sock0 == INVALID_SOCKET ) 
		{
			DebugMsgBox("accept : %d\n", WSAGetLastError());	///<	�ڑ����s
			return false;
		}
		else
		{
			break;
		}
		
	}
	return true;
}


void Server::EndConnect()
{
	// TCP�Z�b�V�����̏I��
	closesocket(m_sock0); 

	// winsock2�̏I������
	WSACleanup();
}