/**
*@file	Connect.cpp
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#include "Connect.h"


//	������
bool Connect::Init()
{
	
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
	m_sock = socket( PF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
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
	
	int nRtn=1;
	char*pt=_buf;
	//�^�C���A�E�g���5�b�ɂ��邽�߂̃��[�v
	while(nRtn && SOCKET_ERROR!=nRtn && 0<(bfSize-(_buf-pt))){
		for(int i=0;i<50;i++){
			nRtn = recv( *GetSocket(), _buf, bfSize-(_buf-pt), 0 );//��M
			if(0<=nRtn) break;
			Sleep(100);
		}
		_buf+=nRtn;
	}
	*_buf='\0';
	
	return (_buf-pt);

	//return true;
}

//	���M���\�b�h
bool Connect::Send( SOCKET* _sock, char *_buf )
{

	int n = send(*_sock, _buf, (int)strlen(_buf), 0);
	if( n == SOCKET_ERROR )
	{
		printf_s("send�F%d\n", WSAGetLastError() );	///<	���M���s
		return false;
	}
	else
	{
		printf_s(_buf);
	}
	return true;
}



//	�ʐM�I��
void Connect::EndConnect()
{
	WSACleanup();
}