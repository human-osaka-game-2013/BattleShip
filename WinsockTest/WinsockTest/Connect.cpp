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
			printf("WSASYSNOTREADY\n");
			break;

		case WSAVERNOTSUPPORTED:///<	�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
			printf("WSAVERNOTSUPPORTED\n");
			break;

		case WSAEINPROGRESS:///<	�u���b�L���O����̎��s���ł��邩�A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			printf("WSAEINPROGRESS\n");
			break;

		case WSAEPROCLIM:	///<	winsock�������ł���ő�v���Z�X���ɒB����
			printf("WSAEPROCLIM\n");
			break;

		case WSAEFAULT:		///<	�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
			printf("WSAEFAULT\n");
			break;
		}
		return false;
	}
	
	MakeSocket();

	SettingSocket();

	return true;
}

//	�\�P�b�g����
bool Connect::MakeSocket()
{
	m_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		printf("error : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

//	���[�`������
void Connect::Control()
{
	EndConnect();
}

//	�ʐM�I��
void Connect::EndConnect()
{
	WSACleanup();
}