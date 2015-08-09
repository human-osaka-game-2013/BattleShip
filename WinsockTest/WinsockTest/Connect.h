/**
*@file	Connect.h
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>
#include <cstdio>

/**
*@brief	�ʐM�Ǘ��N���X
*/
class Connect 
{
private:
	WSADATA	m_wsaData;	///<	Winsock�f�[�^
	SOCKET	m_sock;		///<	�\�P�b�g�����o

public:
	/**
	*@brief	������
	*/
	bool Init();
	
	/**
	*@brief	�\�P�b�g�������\�b�h
	*/
	bool MakeSocket();

	/**
	*@brief	�\�P�b�g�ݒ胁�\�b�h
	*/
	virtual bool SettingSocket() = 0;

	/**
	*@brief	�ʐM�I������
	*/
	virtual void EndConnect();

public:
	WSADATA* GetWsaData(){ return &m_wsaData; }	///<	Winsock�f�[�^�̎擾
	SOCKET*	 GetSocket(){ return &m_sock; }		///<	�\�P�b�g�̎擾
};


#endif