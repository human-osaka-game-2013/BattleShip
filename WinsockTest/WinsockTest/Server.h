/**
*@file	Server.h
*@author	�T�c
*@brief	�T�[�o�[���ʐM�N���X
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "Connect.h"


class Server : public Connect
{
private:
	SOCKET m_sock0;
	struct sockaddr_in m_addr;
	struct sockaddr_in m_client;
	int m_len;

public:
	/**
	*@brief	�\�P�b�g�ݒ胁�\�b�h
	*/
	bool SettingSocket();

	/**
	*@brief	�ڑ��v�����\�b�h
	*/
	bool KeepListen();

	/**
	*@brief	���M���\�b�h
	*/
	bool Send();

	/**
	*@brief	�ʐM�I������
	*/
	void EndConnect();
};

#endif