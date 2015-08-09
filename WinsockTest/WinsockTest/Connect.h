/**
*@file	Connect.h
*@author	亀田
*@brief	通信のテストクラス
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>
#include <cstdio>

/**
*@brief	通信管理クラス
*/
class Connect 
{
private:
	WSADATA	m_wsaData;	///<	Winsockデータ
	SOCKET	m_sock;		///<	ソケットメンバ

public:
	/**
	*@brief	初期化
	*/
	bool Init();
	
	/**
	*@brief	ソケット生成メソッド
	*/
	bool MakeSocket();

	/**
	*@brief	ソケット設定メソッド
	*/
	virtual bool SettingSocket() = 0;

	/**
	*@brief	通信終了処理
	*/
	virtual void EndConnect();

public:
	WSADATA* GetWsaData(){ return &m_wsaData; }	///<	Winsockデータの取得
	SOCKET*	 GetSocket(){ return &m_sock; }		///<	ソケットの取得
};


#endif