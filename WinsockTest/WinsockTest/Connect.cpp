/**
*@file	Connect.cpp
*@author	亀田
*@brief	通信のテストクラス
*/

#include "Connect.h"


//	初期化
bool Connect::Init( bool _bSockType )
{
	m_sockType = _bSockType;
	
	int result = 0;
	result = WSAStartup( MAKEWORD(2,0), &m_wsaData );	///< Winsockの初期化

	if( result != 0 )
	{
		switch(result)
		{
		case WSASYSNOTREADY:///<	ネットワークサブシステムがネットワークへの接続を準備できていない
			DebugMsgBox("WSASYSNOTREADY\n");
			break;

		case WSAVERNOTSUPPORTED:///<	要求されたwinsockのバージョンがサポートされていない
			DebugMsgBox("WSAVERNOTSUPPORTED\n");
			break;

		case WSAEINPROGRESS:///<	ブロッキング操作の実行中であるか、またはサービスプロバイダがコールバック関数を処理している
			DebugMsgBox("WSAEINPROGRESS\n");
			break;

		case WSAEPROCLIM:	///<	winsockが処理できる最大プロセス数に達した
			DebugMsgBox("WSAEPROCLIM\n");
			break;

		case WSAEFAULT:		///<	第二引数であるlpWSAData は有効なポインタではない
			DebugMsgBox("WSAEFAULT\n");
			break;
		}
		return false;
	}
	
	MakeSocket();	///<	ソケット作成

	SettingSocket();	///<	ソケット設定

	return true;
}

//	ソケット生成
bool Connect::MakeSocket()
{
	//	ソケットの生成
	m_sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( m_sock == INVALID_SOCKET ) 
	{
		DebugMsgBox("socket : %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Client::SettingSocket()
{
	if( m_sockType ){
		// 接続先指定用構造体の準備
		m_server.sin_family = AF_INET;
		m_server.sin_port = htons(12345);	///<	ポート番号
		m_server.sin_addr.S_un.S_addr = inet_addr( m_deststr );
	}
	else
	{
		// ソケットの設定
		addr.sin_family = AF_INET;
		addr.sin_port = htons(12345);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		
	}
	return true;
}


//	受信メソッド
bool Connect::Receive( char* _buf, int bfSize )
{
	//int n = 0;
	//memset(_buf, 0, sizeof(_buf));
	////	サーバからのデータ受信
	//n = recv( *GetSocket(), _buf, sizeof(_buf), 0 );
	//if( n == SOCKET_ERROR )
	//{
	//	printf_s("%d, %s\n", n, _buf);
	//	return false;
	//}
	//else
	//{
	//	printf_s(_buf);
	//}
	memset(_buf, 0, sizeof(_buf));

	int nRtn=1;
	char*pt=_buf;
	//タイムアウトを約5秒にするためのループ
	while(nRtn && SOCKET_ERROR!=nRtn && 0<(bfSize-(_buf-pt))){
		for(int i=0;i<50;i++){
			nRtn = recv( *GetSocket(), _buf, bfSize-(_buf-pt), 0 );//受信
			if(0<=nRtn){
				printf_s("recvError：%d\n", WSAGetLastError() );
				break;
			}
			else
			{
				printf_s("通信成功%s\n",_buf);
				Send( &m_sock, m_buf);
				Sleep(100);
			}
		}
		_buf+=nRtn;
	}
	*_buf='\0';
	
	return (_buf-pt)? true: false;

	//return true;
}

//	送信メソッド
bool Connect::Send( SOCKET* _sock, char *_buf )
{

	int n = send(*_sock, _buf, (int)strlen(_buf), 0);
	if( n == SOCKET_ERROR )
	{
		printf_s("sendError：%d\n", WSAGetLastError() );	///<	送信失敗
		return false;
	}
	else
	{
		printf_s("通信成功%s",_buf);
		char tempBuf[_CONECT_SIZE_];
		memset(tempBuf, 0, sizeof(tempBuf));
		Receive( tempBuf, sizeof(tempBuf) );
	}
	return true;
}



//	通信終了
void Connect::EndConnect()
{
	WSACleanup();
}