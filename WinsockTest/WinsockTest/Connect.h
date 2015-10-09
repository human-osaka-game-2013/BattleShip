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
	bool m_sockType;	///<	ソケットの種類
	
	WSADATA	m_wsaData;	///<	Winsockデータ
	SOCKET	m_sock;		///<	ソケットメンバ
	SOCKET	m_sock0;	///<	相手側のソケット情報
	struct sockaddr_in m_addr;	///<	接続先指定用構造体（自身）
	struct sockaddr_in m_client;///<	接続先指定用構造体（クライアント側）
	
public:
	/**
	*@brief	初期化
	*@param[in]	_bSockType	通信を行うタイプ
	*/
	bool Init( bool _bSockType );
	
	/**
	*@brief	ソケット生成メソッド
	*/
	bool MakeSocket();

	/**
	*@brief	ソケット設定メソッド
	*/
	bool SettingSocket();

	/**
	*@brief	ソケットの接続
	*/
	bool Connection();
	
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