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
	struct sockaddr_in m_server;///<	�T�[�o���A�h���X
	
public:
	char* m_deststr;	///<	�T�[�o�[���̃A�h���X�i������j�i�[�|�C���^
	unsigned int** m_addrptr;	///<	IP�A�h���X�i�[
	char m_inbuf[_CONECT_SIZE_];

public:
	/**
	*@brief	�\�P�b�g�ݒ胁�\�b�h
	*/
	bool SettingSocket();

	/**
	*@brief	�ڑ����\�b�h
	*/
	bool ConnectToServer();

	/**
	*@brief	�ʐM�I������
	*/
	void EndConnect();

};

#endif