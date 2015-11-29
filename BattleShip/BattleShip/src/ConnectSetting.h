#ifndef _CONNECTSETTING_H_
#define _CONNECTSETTING_H_

#include "Key.h"
#include "Mouse.h"
#include "LogStream.h"
#include "DirectXFont.h"
#include "read_file.h"

#define _COM_SET_POS_X_	600
#define _IP_TEXT_POS_Y_	400
#define _PORT_TEXT_POS_Y_	550
#define _COM_SET_WIDTH_	200


class ConnectSetting : public ReadFile
{
public:
	class TextField
	{
	public:
		bool	m_settingFlag;
		LogStream m_str;
		float fWidth ,fHeight;

	public:
		TextField(  const char* _str, const long _x, const long _y,
			const float _width, const float _height,
			const unsigned int& _text_w = _LOG_FONT_WIDTH_, const unsigned int& _text_h = _LOG_FONT_HEIGHT_ ): 
			m_str( _str, _x, _y, _text_w, _text_h), fWidth(_width), fHeight(_height)
		{
			m_settingFlag = false;
		}

		void AddStr( const char* _str )
		{
			m_str.AppendStr(_str);
		}

		void ResetStr()
		{
			m_str.DeleteStr();
		}

		bool SelectCheck( float _x, float _y ){
			long tempX, tempY;
			m_str.GetPosition( tempX, tempY );

			if( tempX < static_cast<long>(_x) && tempY + fWidth > static_cast<long>(_x) )
			{
				if(	tempX < static_cast<long>(_y) && tempY + fHeight > static_cast<long>(_y) )
				{
					m_settingFlag = true;
					return m_settingFlag;
				}
			}
			m_settingFlag = false;
			return m_settingFlag;
		}
	};

private:
	CMouse*		m_pMouse;
	CKey*		m_pKey;
	DirectXFont* m_pDXFont;
	TextField	m_ipAddr;
	TextField	m_port;

private:
	bool		sockType;
	std::string strAddr;
	std::string strPort;

public:
	ConnectSetting():
		strAddr(""), strPort(""), 
		m_ipAddr( strAddr.c_str(), _COM_SET_POS_X_, _IP_TEXT_POS_Y_, _COM_SET_WIDTH_, _LOG_FONT_BIGSIZE_),
		m_port( strPort.c_str(), _COM_SET_POS_X_, _PORT_TEXT_POS_Y_, _COM_SET_WIDTH_, _LOG_FONT_BIGSIZE_)
	{
		ReadTableData( _READ_FILE_PASS_1_, 3, 1 );
	}

	void Init( CMouse* const _pMouse, CKey* const _pKey, DirectXFont* const _pDXFont ){
		SetMousePtr( _pMouse );
		SetKeyPtr( _pKey );
	}

	void Control();

	/**
	*@brief	読み取ったデータをテーブルにセット
	*@details	通信設定のデータを外部ファイルから読み取り、それに合うメンバ変数にセットする。
	*/
	void SetTable( char* _p, int _iColumn, int _iLine );

	void SetMousePtr( CMouse* const _pMouse ){ m_pMouse = _pMouse; }
	void SetKeyPtr( CKey* const _pKey ){ m_pKey = _pKey; }
	void SetDXFPtr( DirectXFont* const _pDXFont ){ m_pDXFont = _pDXFont; }
};

#endif