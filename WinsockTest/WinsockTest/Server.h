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
public:
	char m_inbuf[_CONECT_SIZE_];

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

	/**
	*@brief	接続後ソケットの取得
	*/
	SOCKET* GetConnectedSocket(){ return &m_sock0; }
};

#endif