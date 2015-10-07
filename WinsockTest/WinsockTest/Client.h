/**
*@file	Client.h
*@author	亀田
*@brief	クライアント側通信クラス
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "Connect.h"

class Client : public Connect
{
private:
	struct sockaddr_in m_server;///<	サーバ側アドレス
	
public:
	char* m_deststr;	///<	サーバー側のアドレス（文字列）格納ポインタ
	unsigned int** m_addrptr;	///<	IPアドレス格納
	char m_inbuf[_CONECT_SIZE_];

public:
	/**
	*@brief	ソケット設定メソッド
	*/
	bool SettingSocket();

	/**
	*@brief	接続メソッド
	*/
	bool ConnectToServer();

	/**
	*@brief	通信終了処理
	*/
	void EndConnect();

};

#endif