/**
*@file	Connect.cpp
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#include "Connect.h"


//	������
bool Connect::Init( bool _bSockType )
{
	m_sockType = _bSockType;
	
	m_ownSock = NULL;
	m_partnersSock = NULL;
	
	int result = 0;
	result = WSAStartup( MAKEWORD(2,0), &m_wsaData );	///< Winsock�̏�����

	if( result != 0 )
	{
		switch(result)
		{
		case WSASYSNOTREADY:///<	�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ�
			MessageBoxA(0,"WSASYSNOTREADY\n",NULL,MB_OK);
			break;

		case WSAVERNOTSUPPORTED:///<	�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
			MessageBoxA(0,"WSAVERNOTSUPPORTED\n",NULL,MB_OK);
			break;

		case WSAEINPROGRESS:///<	�u���b�L���O����̎��s���ł��邩�A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			MessageBoxA(0,"WSAEINPROGRESS\n",NULL,MB_OK);
			break;

		case WSAEPROCLIM:	///<	winsock�������ł���ő�v���Z�X���ɒB����
			MessageBoxA(0,"WSAEPROCLIM\n",NULL,MB_OK);
			break;

		case WSAEFAULT:		///<	�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
			MessageBoxA(0,"WSAEFAULT\n",NULL,MB_OK);
			break;
		}
		return false;
	}
	
	MakeSocket();	///<	�\�P�b�g�쐬

	return true;
}

//	�\�P�b�g����
bool Connect::MakeSocket()
{
	//	�\�P�b�g�̐���
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
		// �ڑ���w��p�\���̂̏���
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(_ports);	///<	�|�[�g�ԍ�
		m_addr.sin_addr.S_un.S_addr = inet_addr( _domainStr );
	}
	else
	{
		// �\�P�b�g�̐ݒ�
		//	�A�h���X�ƃ|�[�g�ԍ������߂ă\�P�b�g�ɏ��̕R�t�����s��
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(_ports);
		m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
		//	bind�֐��Ń\�P�b�g��IP�A�h���X�ƃ|�[�g�ԍ��Ƒg�ݍ��킹�����āA
		//	�C���^�[�t�F�[�X�̋��͊֌W�����B
		bind( m_ownSock, (struct sockaddr *)&m_addr, sizeof(m_addr));
		
	}
	return true;
}


//	��M���\�b�h
bool Connect::Connection()
{
	if( m_sockType ){
		// �T�[�o�[�ɐڑ�
		if (connect(m_ownSock, (struct sockaddr *)&m_addr, sizeof(m_addr)))
		{
			puts("connect �Ɏ��s���܂���");
			return false;
		}
		
	}
	else{
		// TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
		listen( m_ownSock, 5);
		int len = sizeof( m_client );
		//	�v������������accept�֐��ŗv�����󂯎�����Ƃ������}��������
		//	Client���̃\�P�b�g�f�[�^�����炤
		m_partnersSock = accept( m_ownSock, (struct sockaddr *)&m_client, &len);
		if (m_partnersSock == INVALID_SOCKET)
		{ 
			DebugMsgBox("accept : %d\n", WSAGetLastError());
			return false;
		}
	}
	
	return true;
}

//	��M���\�b�h
bool Connect::Receive( char *_buf, int _bufSize )
{
	//	�O�̂��߃o�b�t�@�[�̏�����
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
		puts("recv �Ɏ��s���܂���");
	    return false;
	}
	return true;
}

//	���M���\�b�h
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
		puts("send �Ɏ��s���܂���");
	    return false;
	}
	return true;
}



//	�ʐM�I��
void Connect::EndConnect()
{
	if( m_partnersSock != NULL )
		closesocket(m_partnersSock);
	
	closesocket(m_ownSock);
	WSACleanup();
}