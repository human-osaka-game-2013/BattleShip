/**
*@file	Client.cpp
*@author	亀田
*@brief	クライアント側通信クラス
*/

#include "Client.h"


bool Client::SettingSocket()
{
	// 接続先指定用構造体の準備
	m_server.sin_family = PF_INET;
	m_server.sin_port = htons(12345);	///<	ポート番号
	m_server.sin_addr.S_un.S_addr = inet_addr( m_deststr );

	return true;
}


bool Client::ConnectToServer()
{
	//	サーバに接続
	//	サーバ側のアドレスチェック？
	if( m_server.sin_addr.S_un.S_addr == 0xffffffff )
	{
		struct hostent *host;
		host = gethostbyname( m_deststr );	///<	通信先名をIPアドレスへ変換
		//	ホストが見つからなかった場合
		if( host == NULL )
		{
			if( WSAGetLastError() == WSAHOST_NOT_FOUND ){
				DebugMsgBox("host not found : %s\n", m_deststr);
			}
			return false;
		}
		/*	--複数のIPアドレスを確認する場合--
			S_addrに欲しいのは32bitの値であり、
			h_addr_listはchar*=8bitの値なので、
			同じくh_addr_listを(int**型へ)変換する。
		*/
		m_addrptr = (unsigned int **)host->h_addr_list;

		while( *m_addrptr != NULL )
		{
			m_server.sin_addr.S_un.S_addr = *(*m_addrptr);
			//	connect()が成功したらloopを抜ける
			if( connect( *GetSocket(),
						(struct sockaddr *)&m_server,
						sizeof( m_server )) == 0 )	{
				break;
			}
			m_addrptr++;

			//recvをノンブロッキングモードにする
			unsigned long val=1;
			ioctlsocket(*GetSocket(), FIONBIO, &val);
			
			//	connectが失敗したら次のアドレスを試す
		}
		//	connectが全て失敗した場合
		if( *m_addrptr == NULL ) {
			DebugMsgBox("connect : %d\n", WSAGetLastError());
			return false;
		}
	}
	//	inet_addr()が成功した時
	else
	{
		//	仮にconnectが失敗した場合はエラー表示
		if( connect( *GetSocket(),
					(struct sockaddr *)&m_server,
					sizeof( m_server )) != 0 ) {
			DebugMsgBox("connect : %d\n", WSAGetLastError());
			return false;
		}
	}

	memset( m_buf, 0, sizeof(m_buf) );
	_snprintf(m_buf, sizeof(m_buf), "Client側が文字列を送りました。");

	return true;
}


void Client::EndConnect()
{

}