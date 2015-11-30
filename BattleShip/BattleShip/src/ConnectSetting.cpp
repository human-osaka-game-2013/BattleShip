#include "ConnectSetting.h"

void ConnectSetting::Init( CMouse* const _pMouse, CKey* const _pKey )
{
	m_serverButton.Init( _COM_SET_POS_X_, _COM_TYPE_BUTTON_POS_Y_,
						_COM_TYPE_BUTTON_WIDTH_, _COM_TYPE_BUTTON_HEIGTH_);
	m_clientButton.Init( _COM_SET_POS_X_+_COM_TYPE_BUTTON_WIDTH_+_COM_TYPE_BUTTON_HEIGTH_, _COM_TYPE_BUTTON_POS_Y_,
						_COM_TYPE_BUTTON_WIDTH_, _COM_TYPE_BUTTON_HEIGTH_);

	SetMousePtr( _pMouse );
	SetKeyPtr( _pKey );

	if( sockType ){
		m_clientButton.SetState( Button::STATE_SELECT );
	}else{
		m_serverButton.SetState( Button::STATE_SELECT );
	}
}

//	外部ファイルの情報をセット
void ConnectSetting::SetTable( char* _p, int _iColumn, int _iLine )
{
	
	switch( _iColumn )
	{
	case 0:
		if( memcmp( _p, "Server", 6) == 0 ){
			sockType = false;
		}else if( memcmp( _p, "Client",6) == 0 ){
			sockType = true;
		}
		break;
	case 1:
		if( sockType ){	///<	ドメイン名が必要なのはクライアント側だけなので
			if( memcmp( _p, "localhost", 9) == 0 ){
				strAddr = "127.0.0.1";
			}else{
				strAddr.append(_p);
			}
		}
		break;
	case 2:
		strPort.append(_p);

		break;
	}
}

void ConnectSetting::Control()
{
	
	const float tempX = static_cast<float>(m_pMouse->GetCursorPosX());
	const float tempY = static_cast<float>(m_pMouse->GetCursorPosY());

	char inputState = 0;
	int pushKey = -1;
	inputState = m_pMouse->GetMouseSt( MOUSE_L );


	//	---サーバーとクライアントの切り替えボタンの処理---
	if( m_serverButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		m_clientButton.SetState( Button::STATE_OFF_CURSOR );
		sockType = false;
	}
	if( m_clientButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		m_serverButton.SetState( Button::STATE_OFF_CURSOR );
		sockType = true;
	}
	//	------
	
	//	IP＆ポート番号のテキストフィールド処理
	if( m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
	{
		m_ipAddr.SelectCheck( tempX, tempY );
		m_port.SelectCheck( tempX, tempY );
	}
	if( m_ipAddr.m_settingFlag )
	{
		pushKey = m_pKey->CheckStateToAllKey( PUSH );
	
	}

}

void ConnectSetting::Draw( CDrawManager* const _pDraw )
{
	float fTempX, fTempY, fTempW, fTempH;
	int tempA, tempR, tempG, tempB;

	m_serverButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_serverButton.GetWidth();
	fTempH = m_serverButton.GetHeight();
	m_serverButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->VertexDraw( _TEX_STARTBUTTON_, fTempX, fTempY, 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f, tempA, tempR, tempG, tempB);

	m_clientButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_clientButton.GetWidth();
	fTempH = m_clientButton.GetHeight();
	m_clientButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->VertexDraw( _TEX_STARTBUTTON_, fTempX, fTempY, 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f, tempA, tempR, tempG, tempB);

	long lTempX, lTempY;
	std::string* pStr;
	LPCSTR lpTempStr;

	m_ipAddr.m_str.GetPosition( lTempX, lTempY );
	fTempW = m_ipAddr.fWidth;
	fTempH = m_ipAddr.fHeight;
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(lTempX), static_cast<float>(lTempY), 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f);

	pStr = m_ipAddr.m_str.GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	_pDraw->m_dxFont.DrawA( lTempX, lTempY, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), lpTempStr);

	m_port.m_str.GetPosition( lTempX, lTempY );
	fTempW = m_port.fWidth;
	fTempH = m_port.fHeight;
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(lTempX), static_cast<float>(lTempY), 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f);

	pStr = m_port.m_str.GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	_pDraw->m_dxFont.DrawA( lTempX, lTempY, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), lpTempStr);
}

