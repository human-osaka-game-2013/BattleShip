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
	m_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

//	��M���\�b�h
bool Connect::Receive( char* _buf )
{
	int n = 0;
	memset(_buf, 0, sizeof(_buf));
	//	�T�[�o����̃f�[�^��M
	n = recv( *GetSocket(), _buf, sizeof(_buf), 0 );
	if( n < 0 )
	{
		DebugMsgBox("%d, %s\n", n, _buf);
		return false;
	}
	printf_s(_buf);
		
	return true;
}

//	���M���\�b�h
bool Connect::Send( SOCKET* _sock, char *_buf )
{

	int n = send(*_sock, _buf, (int)strlen(_buf), 0);
	if( n < 0 )
	{
		DebugMsgBox("send�F%d\n", WSAGetLastError() );	///<	���M���s
		return false;
	}

	return true;
}


//	�ʐM�I��
void Connect::EndConnect()
{
	WSACleanup();
}