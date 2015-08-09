/**
*@file	Server.h
*@author	亀田
*@brief	サーバー側通信クラス
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
	*@brief	ソケット設定メソッド
	*/
	bool SettingSocket();

	/**
	*@brief	接続要求メソッド
	*/
	bool KeepListen();

	/**
	*@brief	送信メソッド
	*/
	bool Send();

	/**
	*@brief	通信終了処理
	*/
	void EndConnect();
};

#endif