#ifndef _CONNECTSETTING_H_
#define _CONNECTSETTING_H_

#include "DrawManager.h"
#include "Button.h"
#include "Mouse.h"
#include "Key.h"
#include "read_file.h"
#include "TextField.h"

#define _COM_SET_POS_X_	700
#define	_COM_TYPE_BUTTON_POS_Y_	300
#define	_COM_TYPE_BUTTON_WIDTH_	80
#define	_COM_TYPE_BUTTON_HEIGTH_ 30

#define _IP_TEXT_POS_Y_	400
#define _PORT_TEXT_POS_Y_	500
#define _COM_SET_WIDTH_	200

class ConnectSetting : public ReadFile
{
private:
	bool		sockType;
	std::string strAddr;
	std::string strPort;

private:
	CMouse*		m_pMouse;	///< マウスポインタ
	CKey*		m_pKey;		///< キーポインタ
	TextField	m_ipAddr;	///< IPアドレステキストフィールド
	TextField	m_port;		///< ポート番号テキストフィールド
	Button		m_serverButton;	///< サーバーボタン 
	Button		m_clientButton;	///< クライアントボタン

public:
	ConnectSetting():
		strAddr(""), strPort(""), 
		m_ipAddr( strAddr.c_str(), _COM_SET_POS_X_, _IP_TEXT_POS_Y_, _COM_SET_WIDTH_, _LOG_FONT_BIGSIZE_),
		m_port( strPort.c_str(), _COM_SET_POS_X_, _PORT_TEXT_POS_Y_, _COM_SET_WIDTH_, _LOG_FONT_BIGSIZE_)
	{
		ReadTableData( _READ_FILE_PASS_1_, 3, 1 );
		m_ipAddr.ResetStr();
		m_ipAddr.AddStr(strAddr.c_str());
		m_port.ResetStr();
		m_port.AddStr(strPort.c_str());
	}

	void Init( CMouse* const _pMouse, CKey* const _pKey );

	void Control();

	void Draw( CDrawManager* const _pDraw );

	/**
	*@brief	読み取ったデータをテーブルにセット
	*@details	通信設定のデータを外部ファイルから読み取り、それに合うメンバ変数にセットする。
	*/
	void SetTable( char* _p, int _iColumn, int _iLine );

	void SetMousePtr( CMouse* const _pMouse ){ m_pMouse = _pMouse; }
	void SetKeyPtr( CKey* const _pKey ){ m_pKey = _pKey; }
	//void SetDXFPtr( DirectXFont* const _pDXFont ){ m_pDXFont = _pDXFont; }
};

#endif