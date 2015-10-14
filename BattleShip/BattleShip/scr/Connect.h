/**
*@file	Connect.h
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>

#include"DebugInterface.h"


/**
*@brief	�ʐM�Ǘ��N���X
*/
class Connect :public ReadFile
{
private:
	bool m_sockType;	///<	�\�P�b�g�̃t���O�itrue�FClient�Afalse�FServer�j
	
	WSADATA	m_wsaData;	///<	Winsock�f�[�^
	SOCKET	m_ownSock;		///<	�\�P�b�g�����o
	SOCKET	m_partnersSock;	///<	���葤�̃\�P�b�g���
	struct 	sockaddr_in m_addr;	///<	�ڑ���w��p�\���́i���g�j
	struct 	sockaddr_in m_client;///<	�ڑ���w��p�\���́i�N���C�A���g���j
	char* 	m_domainStr;///<	�T�[�o�[���̃h���C�����i�N���C�A���g���j
	int		m_ports;	///<	�T�[�o�[���̃|�[�g�ԍ��i�N���C�A���g���j
	
public:
	/**
	*@brief	������
	*@param[in]	_bSockType	�ʐM���s���^�C�v
	*/
	bool Init( bool _bSockType );
	
	/**
	*@brief	�\�P�b�g�ݒ胁�\�b�h
	*/
	bool SettingSocket( int _ports, char* _domainStr );

	/**
	*@brief	�\�P�b�g�̐ڑ�
	*/
	bool Connection();

	/**
	*@brief	��M���\�b�h
	*@warning	�p�ӂ����o�b�t�@�[�i_buf�j�Ƒ��T�C�Y�i_bufSize�j�͓����ɂ��Ă��������B
	*@param[out] _buf	recv�֐��ő��葤���瑗��ꂽ�f�[�^�̊i�[�p�o�b�t�@�[�i�����l�������Ă���ꍇ��0�ŏ����������̂Œ��Ӂj
	*@param[in]	 _bufSize	recv�֐��Ŏ󂯎��f�[�^�T�C�Y�i���葤�Ɠ����łȂ��ƃG���[�̊�ɂȂ�܂��B�j
	*@retval true	recv�ɐ���
	*@retval false	recv�Ɏ��s
	*/
	bool Receive( char* _buf, int _bufSize );
	
	/**
	*@brief	���M���\�b�h
	*@warning	�p�ӂ����o�b�t�@�[�i_buf�j�Ƒ��T�C�Y�i_bufSize�j�͓����ɂ��Ă��������B
	*@param[out] _buf	send�֐��ő��葤�֑���f�[�^�̈�
	*@param[in]	 _bufSize	send�֐��ő���f�[�^�T�C�Y�i���葤�Ɠ����łȂ��ƃG���[�̊�ɂȂ�܂��B�j
	*@retval true	send�ɐ���
	*@retval false	send�Ɏ��s
	*/
	bool Send( char *_buf, int _bufSize );
	
	/**
	*@brief	�ʐM�I������
	*/
	void EndConnect();

private:
	/**
	*@brief	�\�P�b�g�������\�b�h
	*/
	bool MakeSocket();

};


#endif