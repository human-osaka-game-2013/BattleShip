/**
*@file	Connect.h
*@author	亀田
*@brief	通信のテストクラス
*@warning	このヘッダーはwinsock2.hをインクルードしていて、
			windows.hの仕様上、旧バージョンのWinsockと定数の再定義がされてしまいます。
			再定義を回避するにはこのヘッダーななるべく一番最初にインクルードしてください。
			他のSDK系のヘッダー内にもwindows.hが宣言されていることも確認しましたので、
			なるべくそのようなヘッダーと一緒にしないようにもお願いします。
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

//----Winsock定数の再定義回避処理----
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
//----ここまで----

#include "DebugInterface.h"
#include "read_file.h"
#include "ConnectStruct.h"


#define _RECV_TIMEOUT_SECOND_	0.3	///< 受信のタイムアウトをするまでの秒数

/**
*@brief	通信管理クラス
*/
class Connect : public ReadFile
{
public:
	bool m_sockType;	///<	ソケットのフラグ（true：Client、false：Server）

private:	
	WSADATA	m_wsaData;		///< Winsockデータ
	SOCKET	m_ownSock;		///< ソケットメンバ
	SOCKET	m_partnersSock;	///< 相手側のソケット情報
	struct 	sockaddr_in m_addr;		///< 接続先指定用構造体（自身）
	struct 	sockaddr_in m_client;	///< 接続先指定用構造体（クライアント側）
	std::string 	m_domainStr;///< サーバー側のドメイン名（orIPアドレス）（クライアント時）
	int		m_ports;			///< サーバー側のポート番号（クライアント時）
	fd_set	m_fds, m_readfds;	///< select関数に渡す為のソケットデータコピー用
	int m_selectResult;		///< selectの結果
	struct timeval m_tv;	///< selectでのタイムアウト用

private:
	/**
	*@brief	通信に必要なデータの種類
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
	*@brief	初期化
	*/
	bool Init();
	
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
	bool Send( char* _buf, int _bufSize );
	
	/**
	*@brief	通信終了処理
	*/
	void EndConnect();

private:
	/**
	*@brief	読み取ったデータをテーブルにセット
	*@details	通信に必要なデータを外部ファイルから読み取り、それに合うメンバ変数にセットする。
	*/
	void SetTable( char* _p, int _iColumn, int _iLine );

	/**
	*@brief	ソケット設定メソッド
	*/
	bool SettingSocket();

	/**
	*@brief	ソケット生成メソッド
	*/
	bool MakeSocket();

};


#endif