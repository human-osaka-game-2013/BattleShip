/**
*@file	ConnectManager.h
*@author	亀田
*@brief	通信のテストクラス
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <winsock2.h>

/**
*@brief	通信管理クラス
*/
class ConnectManager 
{
private:
	WSADATA	m_wsaData;	///<	
	SOCKET	m_sock;		///<	

public:
	/**
	*@brief	初期化
	*/
	bool Init();
	
	/**
	*@brief	ルーチン処理
	*/
	void Control();

	/**
	*@brief	通信終了処理
	*/
	void EndConnect();
};


#endif