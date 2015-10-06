/**
*@file	Connect.h
*@author	亀田
*@brief	通信のテストクラス
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>
#include "DebugInterface.h"

#define _CONECT_SIZE_ 2048

/**
*@brief	通信管理クラス
*/
class Connect 
{
private:
	WSADATA	m_wsaData;	///<	Winsockデータ
	SOCKET	m_sock;		///<	ソケットメンバ

protected:
	char	m_buf[_CONECT_SIZE_];

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
	*@brief	受信メソッド
	*/
	bool Receive( char* _buf, int bfSize );
	
	/**
	*@brief	送信メソッド
	*/
	bool Send( SOCKET* _sock, char *_buf );

	/**
	*@brief	通信終了処理
	*/
	virtual void EndConnect();

	/**
	*@brief	文字列取得
	*/
	char* GetBuf(){ return m_buf; }

public:
	WSADATA* GetWsaData(){ return &m_wsaData; }	///<	Winsockデータの取得
	SOCKET*	 GetSocket(){ return &m_sock; }		///<	ソケットの取得
};


#endif