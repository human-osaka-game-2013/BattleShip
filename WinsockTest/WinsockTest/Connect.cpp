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
			DebugMsgBox("WSASYSNOTREADY\n");
			break;

		case WSAVERNOTSUPPORTED:///<	�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
			DebugMsgBox("WSAVERNOTSUPPORTED\n");
			break;

		case WSAEINPROGRESS:///<	�u���b�L���O����̎��s���ł��邩�A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			DebugMsgBox("WSAEINPROGRESS\n");
			break;

		case WSAEPROCLIM:	///<	winsock�������ł���ő�v���Z�X���ɒB����
			DebugMsgBox("WSAEPROCLIM\n");
			break;

		case WSAEFAULT:		///<	�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
			DebugMsgBox("WSAEFAULT\n");
			break;
		}
		return false;
	}
	
	MakeSocket();	///<	�\�P�b�g�쐬

	SettingSocket();	///<	�\�P�b�g�ݒ�

	return true;
}

//	�\�P�b�g����
bool Connect::MakeSocket()
{
	//	�\�P�b�g�̐���
	m_ownSock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Client::SettingSocket( int _ports, char* _domainStr )
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
		bind( m_ownSock, (struct sockaddr *)&addr, sizeof(addr));
		
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
			getch();
			return -1;
		}
		
	}
	else{
		// TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
		listen( ownSock, 5);
		int len = sizeof( m_client );
		//	�v������������accept�֐��ŗv�����󂯎�����Ƃ������}��������
		//	Client���̃\�P�b�g�f�[�^�����炤
		m_partnersSock = accept( m_onwSock, (struct sockaddr *)&m_client, &len);
		if (m_partnersSock == INVALID_SOCKET)
		{   printf("accept : %d\n", WSAGetLastError());
		    
		}
	}
	
	//int n = 0;
	//memset(_buf, 0, sizeof(_buf));
	////	�T�[�o����̃f�[�^��M
	//n = recv( *GetSocket(), _buf, sizeof(_buf), 0 );
	//if( n == SOCKET_ERROR )
	//{
	//	printf_s("%d, %s\n", n, _buf);
	//	return false;
	//}
	//else
	//{
	//	printf_s(_buf);
	//}
	//memset(_buf, 0, sizeof(_buf));
    //
	//int nRtn=1;
	//char*pt=_buf;
	////�^�C���A�E�g���5�b�ɂ��邽�߂̃��[�v
	//while(nRtn && SOCKET_ERROR!=nRtn && 0<(bfSize-(_buf-pt))){
	//	for(int i=0;i<50;i++){
	//		nRtn = recv( *GetSocket(), _buf, bfSize-(_buf-pt), 0 );//��M
	//		if(0<=nRtn){
	//			printf_s("recvError�F%d\n", WSAGetLastError() );
	//			break;
	//		}
	//		else
	//		{
	//			printf_s("�ʐM����%s\n",_buf);
	//			Send( &m_sock, m_buf);
	//			Sleep(100);
	//		}
	//	}
	//	_buf+=nRtn;
	//}
	//*_buf='\0';
	//
	//return (_buf-pt)? true: false;

	//return true;
}

//	��M���\�b�h
bool Connect::Receive( char *_buf, int _bufSize )
{
	//	�O�̂��߃o�b�t�@�[�̏�����
	memset(_buf,0,_bufSize);
	
	recv(sockw, (char*)testBuf, bufSize, 0 );
	if (n < 0)
	{   puts("recv �Ɏ��s���܂���");
	    getch();
	    return false;
	}
	return true;
}

//	���M���\�b�h
bool Connect::Send( char *_buf, int _bufSize )
{
	n= send(sockw, (const char*)testObj, bufSize, 0);
	if (n < 0)
	{   puts("send �Ɏ��s���܂���");
	    getch();
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