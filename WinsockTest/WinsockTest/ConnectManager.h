/**
*@file	ConnectManager.h
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>

/**
*@brief	�ʐM�Ǘ��N���X
*/
class ConnectManager 
{
private:
	WSADATA	m_wsaData;	///<	
	SOCKET	m_sock;		///<	

public:
	/**
	*@brief	������
	*/
	bool Init();
	
	/**
	*@brief	���[�`������
	*/
	void Control();

	/**
	*@brief	�ʐM�I������
	*/
	void EndConnect();
};


#endif