/**
*@file	Client.h
*@author	�T�c
*@brief	�N���C�A���g���ʐM�N���X
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "Connect.h"

class Client : public Connect
{
private:
	struct sockaddr_in m_server;
	char m_buf[32];

public:
	/**
	*@brief	�\�P�b�g�ݒ胁�\�b�h
	*/
	void SettingSocket();

	/**
	*@brief	�ʐM�I������
	*/
	void EndConnect();
};

#endif