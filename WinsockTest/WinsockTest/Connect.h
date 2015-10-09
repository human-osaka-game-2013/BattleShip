/**
*@file	Connect.h
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>
#include "DebugInterface.h"

#define _CONECT_SIZE_ 2048

/**
*@brief	�ʐM�Ǘ��N���X
*/
class Connect 
{
private:
	bool m_sockType;	///<	�\�P�b�g�̎��
	
	WSADATA	m_wsaData;	///<	Winsock�f�[�^
	SOCKET	m_sock;		///<	�\�P�b�g�����o
	SOCKET	m_sock0;	///<	���葤�̃\�P�b�g���
	struct sockaddr_in m_addr;	///<	�ڑ���w��p�\���́i���g�j
	struct sockaddr_in m_client;///<	�ڑ���w��p�\���́i�N���C�A���g���j
	
public:
	/**
	*@brief	������
	*@param[in]	_bSockType	�ʐM���s���^�C�v
	*/
	bool Init( bool _bSockType );
	
	/**
	*@brief	�\�P�b�g�������\�b�h
	*/
	bool MakeSocket();

	/**
	*@brief	�\�P�b�g�ݒ胁�\�b�h
	*/
	bool SettingSocket();

	/**
	*@brief	�\�P�b�g�̐ڑ�
	*/
	bool Connection();
	
	/**
	*@brief	��M���\�b�h
	*/
	bool Receive( char* _buf, int bfSize );
	
	/**
	*@brief	���M���\�b�h
	*/
	bool Send( SOCKET* _sock, char *_buf );

	/**
	*@brief	�ʐM�I������
	*/
	virtual void EndConnect();

	/**
	*@brief	������擾
	*/
	char* GetBuf(){ return m_buf; }

public:
	WSADATA* GetWsaData(){ return &m_wsaData; }	///<	Winsock�f�[�^�̎擾
	SOCKET*	 GetSocket(){ return &m_sock; }		///<	�\�P�b�g�̎擾
};


#endif