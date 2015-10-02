/**
*@file	Client.cpp
*@author	�T�c
*@brief	�N���C�A���g���ʐM�N���X
*/

#include "Client.h"


bool Client::SettingSocket()
{
	// �ڑ���w��p�\���̂̏���
	m_server.sin_family = PF_INET;
	m_server.sin_port = htons(12345);	///<	�|�[�g�ԍ�
	m_server.sin_addr.S_un.S_addr = inet_addr( m_deststr );

	return true;
}


bool Client::ConnectToServer()
{
	//	�T�[�o�ɐڑ�
	//	�T�[�o���̃A�h���X�`�F�b�N�H
	if( m_server.sin_addr.S_un.S_addr == 0xffffffff )
	{
		struct hostent *host;
		host = gethostbyname( m_deststr );	///<	�ʐM�於��IP�A�h���X�֕ϊ�
		//	�z�X�g��������Ȃ������ꍇ
		if( host == NULL )
		{
			if( WSAGetLastError() == WSAHOST_NOT_FOUND ){
				DebugMsgBox("host not found : %s\n", m_deststr);
			}
			return false;
		}
		/*	--������IP�A�h���X���m�F����ꍇ--
			S_addr�ɗ~�����̂�32bit�̒l�ł���A
			h_addr_list��char*=8bit�̒l�Ȃ̂ŁA
			������h_addr_list��(int**�^��)�ϊ�����B
		*/
		m_addrptr = (unsigned int **)host->h_addr_list;

		while( *m_addrptr != NULL )
		{
			m_server.sin_addr.S_un.S_addr = *(*m_addrptr);
			//	connect()������������loop�𔲂���
			if( connect( *GetSocket(),
						(struct sockaddr *)&m_server,
						sizeof( m_server )) == 0 )	{
				break;
			}
			m_addrptr++;

			//recv���m���u���b�L���O���[�h�ɂ���
			unsigned long val=1;
			ioctlsocket(*GetSocket(), FIONBIO, &val);
			
			//	connect�����s�����玟�̃A�h���X������
		}
		//	connect���S�Ď��s�����ꍇ
		if( *m_addrptr == NULL ) {
			DebugMsgBox("connect : %d\n", WSAGetLastError());
			return false;
		}
	}
	//	inet_addr()������������
	else
	{
		//	����connect�����s�����ꍇ�̓G���[�\��
		if( connect( *GetSocket(),
					(struct sockaddr *)&m_server,
					sizeof( m_server )) != 0 ) {
			DebugMsgBox("connect : %d\n", WSAGetLastError());
			return false;
		}
	}

	memset( m_buf, 0, sizeof(m_buf) );
	_snprintf(m_buf, sizeof(m_buf), "Client����������𑗂�܂����B");

	return true;
}


void Client::EndConnect()
{

}