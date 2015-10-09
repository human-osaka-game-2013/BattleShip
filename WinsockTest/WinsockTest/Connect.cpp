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
	m_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Client::SettingSocket()
{
	if( m_sockType ){
		// �ڑ���w��p�\���̂̏���
		m_server.sin_family = AF_INET;
		m_server.sin_port = htons(12345);	///<	�|�[�g�ԍ�
		m_server.sin_addr.S_un.S_addr = inet_addr( m_deststr );
	}
	else
	{
		// �\�P�b�g�̐ݒ�
		addr.sin_family = AF_INET;
		addr.sin_port = htons(12345);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		
	}
	return true;
}


//	��M���\�b�h
bool Connect::Receive( char* _buf, int bfSize )
{
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
	memset(_buf, 0, sizeof(_buf));

	int nRtn=1;
	char*pt=_buf;
	//�^�C���A�E�g���5�b�ɂ��邽�߂̃��[�v
	while(nRtn && SOCKET_ERROR!=nRtn && 0<(bfSize-(_buf-pt))){
		for(int i=0;i<50;i++){
			nRtn = recv( *GetSocket(), _buf, bfSize-(_buf-pt), 0 );//��M
			if(0<=nRtn){
				printf_s("recvError�F%d\n", WSAGetLastError() );
				break;
			}
			else
			{
				printf_s("�ʐM����%s\n",_buf);
				Send( &m_sock, m_buf);
				Sleep(100);
			}
		}
		_buf+=nRtn;
	}
	*_buf='\0';
	
	return (_buf-pt)? true: false;

	//return true;
}

//	���M���\�b�h
bool Connect::Send( SOCKET* _sock, char *_buf )
{

	int n = send(*_sock, _buf, (int)strlen(_buf), 0);
	if( n == SOCKET_ERROR )
	{
		printf_s("sendError�F%d\n", WSAGetLastError() );	///<	���M���s
		return false;
	}
	else
	{
		printf_s("�ʐM����%s",_buf);
		char tempBuf[_CONECT_SIZE_];
		memset(tempBuf, 0, sizeof(tempBuf));
		Receive( tempBuf, sizeof(tempBuf) );
	}
	return true;
}



//	�ʐM�I��
void Connect::EndConnect()
{
	WSACleanup();
}