/**
*@file	Connect.h
*@author	亀田
*@brief	通信のテストクラス
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>

#include"DebugInterface.h"


/**
*@brief	通信管理クラス
*/
class Connect :public ReadFile
{
private:
	bool m_sockType;	///<	ソケットのフラグ（true：Client、false：Server）
	
	WSADATA	m_wsaData;	///<	Winsockデータ
	SOCKET	m_ownSock;		///<	ソケットメンバ
	SOCKET	m_partnersSock;	///<	相手側のソケット情報
	struct 	sockaddr_in m_addr;	///<	接続先指定用構造体（自身）
	struct 	sockaddr_in m_client;///<	接続先指定用構造体（クライアント側）
	char* 	m_domainStr;///<	サーバー側のドメイン名（クライアント時）
	int		m_ports;	///<	サーバー側のポート番号（クライアント時）
	
public:
	/**
	*@brief	初期化
	*@param[in]	_bSockType	通信を行うタイプ
	*/
	bool Init( bool _bSockType );
	
	/**
	*@brief	ソケット設定メソッド
	*/
	bool SettingSocket( int _ports, char* _domainStr );

	/**
	*@brief	ソケットの接続
	*/
	bool Connection();

	/**
	*@brief	受信メソッド
	*@warning	用意したバッファー（_buf）と総サイズ（_bufSize）は同じにしてください。
	*@param[out] _buf	recv関数で相手側から送られたデータの格納用バッファー（何か値が入っている場合は0で初期化されるので注意）
	*@param[in]	 _bufSize	recv関数で受け取るデータサイズ（相手側と同じでないとエラーの基になります。）
	*@retval true	recvに成功
	*@retval false	recvに失敗
	*/
	bool Receive( char* _buf, int _bufSize );
	
	/**
	*@brief	送信メソッド
	*@warning	用意したバッファー（_buf）と総サイズ（_bufSize）は同じにしてください。
	*@param[out] _buf	send関数で相手側へ送るデータ領域
	*@param[in]	 _bufSize	send関数で送るデータサイズ（相手側と同じでないとエラーの基になります。）
	*@retval true	sendに成功
	*@retval false	sendに失敗
	*/
	bool Send( char *_buf, int _bufSize );
	
	/**
	*@brief	通信終了処理
	*/
	void EndConnect();

private:
	/**
	*@brief	ソケット生成メソッド
	*/
	bool MakeSocket();

};


#endif