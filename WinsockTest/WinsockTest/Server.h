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
	SOCKET m_sock0;	///<	接続後ソケット
	struct sockaddr_in m_addr;	///<	サーバ側アドレス
	struct sockaddr_in m_client;///<	クライアント側アドレス
	int m_len;	///<	送信メッセージの長さ
	bool m_reuseFlag;	///<	SO_REUSEADDR有効用

	//----HTTPサーバサンプルテスト用
	char m_buf[2048];
	char m_inbuf[2048];

	//----
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
	*@brief	通信終了処理
	*/
	void EndConnect();
};

#endif