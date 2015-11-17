/**
*@file	Connect.h
*@author	�T�c
*@brief	�ʐM�̃e�X�g�N���X
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include "DebugInterface.h"
#include "read_file.h"
#include "ConnectStruct.h"

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define _RECV_TIMEOUT_SECOND_	1	///< ��M�̃^�C���A�E�g������܂ł̕b��

/**
*@brief	�ʐM�Ǘ��N���X
*/
class Connect : public ReadFile
{
public:
	bool m_sockType;	///<	�\�P�b�g�̃t���O�itrue�FClient�Afalse�FServer�j

private:	
	WSADATA	m_wsaData;		///< Winsock�f�[�^
	SOCKET	m_ownSock;		///< �\�P�b�g�����o
	SOCKET	m_partnersSock;	///< ���葤�̃\�P�b�g���
	struct 	sockaddr_in m_addr;		///< �ڑ���w��p�\���́i���g�j
	struct 	sockaddr_in m_client;	///< �ڑ���w��p�\���́i�N���C�A���g���j
	std::string 	m_domainStr;///< �T�[�o�[���̃h���C�����iorIP�A�h���X�j�i�N���C�A���g���j
	int		m_ports;			///< �T�[�o�[���̃|�[�g�ԍ��i�N���C�A���g���j
	fd_set	m_fds, m_readfds;	///< select�֐��ɓn���ׂ̃\�P�b�g�f�[�^�R�s�[�p
	int m_selectResult;		///< select�̌���
	struct timeval m_tv;	///< select�ł̃^�C���A�E�g�p

private:
	/**
	*@brief	�ʐM�ɕK�v�ȃf�[�^�̎��
	*/
	enum _CONNECT_INFO_TYPE_
	{
		SOCK_TYPE,
		DOMAIN_STR,
		PORTS_NUM,
		CONNECT_INFO_MAX
	};

public:
	~Connect()
	{
		EndConnect();
	}

public:
	/**
	*@brief	������
	*/
	bool Init();
	
	/**
	*@brief	�ǂݎ�����f�[�^���e�[�u���ɃZ�b�g
	*@details	�ʐM�ɕK�v�ȃf�[�^���O���t�@�C������ǂݎ��A����ɍ��������o�ϐ��ɃZ�b�g����B
	*/
	void SetTable( char* _p, int _iColumn, int _iLine );

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