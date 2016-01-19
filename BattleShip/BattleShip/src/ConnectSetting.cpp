#include "ConnectSetting.h"
#include "DebugInterface.h"

void ConnectSetting::Init( CMouse* const _pMouse, CKey* const _pKey, Audio* const _pAudio )
{
	m_serverButton.Init( _COM_SET_POS_X_,
						 _COM_TYPE_BUTTON_POS_Y_,
						 _COM_TYPE_BUTTON_WIDTH_, 
						 _COM_TYPE_BUTTON_HEIGTH_,
						 _pAudio );

	m_clientButton.Init( _COM_SET_POS_X_+_COM_TYPE_BUTTON_WIDTH_+_COM_TYPE_BUTTON_HEIGTH_,
						 _COM_TYPE_BUTTON_POS_Y_,
						 _COM_TYPE_BUTTON_WIDTH_, 
						 _COM_TYPE_BUTTON_HEIGTH_,
						 _pAudio );

	m_updateButton.Init( m_clientButton.GetPositionX(),
						 _UPDATE_BUTTON_POS_Y_,
						 _COM_TYPE_BUTTON_WIDTH_,
						 _COM_TYPE_BUTTON_HEIGTH_,
						 _pAudio );

	SetMousePtr( _pMouse );
	SetKeyPtr( _pKey );
	SetAudioPtr( _pAudio );

	if ( sockType ) {
		m_clientButton.SetState( Button::STATE_SELECT );
	}else {
		m_serverButton.SetState( Button::STATE_SELECT );
	}
}

//	外部ファイルの情報をセット
void ConnectSetting::SetTable( char* _p, int _iColumn, int _iLine )
{
	
	switch ( _iColumn )
	{
	case 0:
		if ( memcmp( _p, "Server", 6) == 0 ){
			sockType = false;
		}else if ( memcmp( _p, "Client",6) == 0 ){
			sockType = true;
		}
		break;
	case 1:
		if ( sockType ) {	///<	ドメイン名が必要なのはクライアント側だけなので
			if ( memcmp( _p, "localhost", 9) == 0 ) {
				strAddr = "127.0.0.1";
			}else {
				strAddr.append(_p);
				strAddr.pop_back();
			}
		}else {
			if ( memcmp( _p, "localhost", 9) == 0 ) {
				strAddr = "127.0.0.1";
			}else {
				strAddr.append(_p);
				strAddr.pop_back();
			}
		}
		break;
	case 2:
		strPort.append(_p);

		break;
	}
}


bool ConnectSetting::ConvertDataFileFromStr( std::string* _outStr )
{
	//	念のため文字列をリセット
	_outStr->erase();
	std::string* pTempStr;

	//	サーバーorクライアント
	if ( sockType ){
		_outStr->append("Client\n");
	}else{
		_outStr->append("Server\n");
	}

	//	アドレス
	pTempStr = m_ipAddr.m_str.GetStringPtr();
	if ( pTempStr->size() < _IP_STR_MIN_ || pTempStr->size() > _IP_STR_MAX_ ){
		//	アドレスが入力（or数値が足らない）されていなかったら、ダミーとしてローカルホストを入れる
		DebugMsgBox("IPが入力されていません。またはIPアドレスとして認識出来ませんでした。確認してください。");
		_outStr->append("localhost\n");
		strAddr = "127.0.0.1";
	}else{
		_outStr->append( pTempStr->c_str() );
		_outStr->append("\n");
		strAddr = pTempStr->c_str();
	}

	m_ipAddr.ResetStr();
	m_ipAddr.AddStr(strAddr.c_str());

	//	ポート
	pTempStr = m_port.m_str.GetStringPtr();
	if ( pTempStr->size() <= 2 ){
		//	ポート番号が入力（or数値が足らない）されていなかったら、失敗とみなす。
		DebugMsgBox("ポート番号が入力されていません。確認してください。");
		return false;
	}else{
		_outStr->append( pTempStr->c_str() );
		strPort = pTempStr->c_str();
	}

	m_port.ResetStr();
	m_port.AddStr(strPort.c_str());

	return true;
}

void ConnectSetting::Control()
{
	
	const float tempX = static_cast<float>(m_pMouse->GetCursorPosX());
	const float tempY = static_cast<float>(m_pMouse->GetCursorPosY());

	char inputState = 0;
	int pushKey = -1;
	inputState = m_pMouse->GetMouseSt( MOUSE_L );


	//	---サーバーとクライアントの切り替えボタンの処理---
	if ( m_serverButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		m_clientButton.SetState( Button::STATE_OFF_CURSOR );
		sockType = false;
	}
	if ( m_clientButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		m_serverButton.SetState( Button::STATE_OFF_CURSOR );
		sockType = true;
	}

	//	通信設定情報の更新ボタンの処理
	//	すでにクリックされていたら一度状態をリセット
	if ( m_updateButton.GetState() == Button::STATE_SELECT )
	{
		m_updateButton.SetState( Button::STATE_OFF_CURSOR );
	}

	//	押されていたら
	if ( m_updateButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		//	ファイルデータを更新する。
		std::string tempStr;
		if ( !ConvertDataFileFromStr( &tempStr ))
			m_serverButton.SetState( Button::STATE_OFF_CURSOR );
		SetDataFile( tempStr );
	}
	
	//	IP＆ポート番号のテキストフィールド処理
	if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
	{
		bool ipSetting = false, portSetting = false;
		ipSetting = m_ipAddr.SelectCheck( tempX, tempY );
		portSetting = m_port.SelectCheck( tempX, tempY );

		if (ipSetting || portSetting)
		{
			m_pAudio->SoundPlay( Audio::_FAILED_SE_ );
		}
	}
	//	IPアドレスのテキストフィールドが選択中
	if ( m_ipAddr.m_settingFlag )
	{
		pushKey = m_pKey->CheckStateToAllKey( PUSH );
		if ( pushKey != -1 ){
			m_ipAddr.AddStr( pushKey );
		}
	}
	//	ポート番号のテキストフィールドが選択中
	if ( m_port.m_settingFlag )
	{
		pushKey = m_pKey->CheckStateToAllKey( PUSH );
		if ( pushKey != -1 ){
			m_port.AddStr( pushKey );
		}
	}
	
}

void ConnectSetting::Draw( CDrawManager* const _pDraw )
{
	float fTempX, fTempY, fTempW, fTempH;
	int tempA, tempR, tempG, tempB;
	long lTempX, lTempY;
	std::string* pStr;
	LPCSTR lpTempStr;

	//	通信設定ボックスの
	m_port.m_str.GetPosition( lTempX, lTempY );
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(_COM_SET_POS_X_-_COM_TYPE_BUTTON_HEIGTH_),
		static_cast<float>(_COM_TYPE_BUTTON_POS_Y_-_COM_TYPE_BUTTON_HEIGTH_), 
		static_cast<float>((_COM_TYPE_BUTTON_WIDTH_*2)+(_COM_TYPE_BUTTON_HEIGTH_*3)), 
		static_cast<float>((_UPDATE_BUTTON_POS_Y_-_COM_TYPE_BUTTON_POS_Y_)+(_COM_TYPE_BUTTON_HEIGTH_*3)), 
		0.f, 0.f, 1.f, 1.f, 200, 150, 150, 150);

	//	サーバーボタン描画
	m_serverButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_serverButton.GetWidth();
	fTempH = m_serverButton.GetHeight();
	m_serverButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->AnimationDraw( _TEX_BUTTONMAP_,fTempX,fTempY,
						   fTempW,fTempH,false,false,0,0,
						   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	クライアントボタン描画
	m_clientButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_clientButton.GetWidth();
	fTempH = m_clientButton.GetHeight();
	m_clientButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->AnimationDraw( _TEX_BUTTONMAP_,fTempX,fTempY,
						   fTempW,fTempH,false,false,0,1,
						   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	情報設定更新ボタン描画
	m_updateButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_updateButton.GetWidth();
	fTempH = m_updateButton.GetHeight();
	m_updateButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->AnimationDraw( _TEX_BUTTONMAP_,fTempX,fTempY,
						   fTempW,fTempH,false,false,0,2,
						   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	IPテキストフィールド描画
	m_ipAddr.m_str.GetPosition( lTempX, lTempY );
	fTempW = m_ipAddr.fWidth;
	fTempH = m_ipAddr.fHeight;
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(lTempX), static_cast<float>(lTempY), 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f);

	//	IP文字列描画
	pStr = m_ipAddr.m_str.GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	_pDraw->m_dxFont.DrawA( lTempX, lTempY, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), lpTempStr);
	_pDraw->m_dxFont.DrawA( lTempX-_LOG_FONT_BIGSIZE_, lTempY-_LOG_FONT_BIGSIZE_, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), "IPアドレス");

	//	ポートテキストフィールド描画
	m_port.m_str.GetPosition( lTempX, lTempY );
	fTempW = m_port.fWidth;
	fTempH = m_port.fHeight;
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(lTempX), static_cast<float>(lTempY), 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f);

	//	ポート文字列描画
	pStr = m_port.m_str.GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	_pDraw->m_dxFont.DrawA( lTempX, lTempY, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), lpTempStr);
	_pDraw->m_dxFont.DrawA( lTempX-_LOG_FONT_BIGSIZE_, lTempY-_LOG_FONT_BIGSIZE_, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), "ポート番号");
}

