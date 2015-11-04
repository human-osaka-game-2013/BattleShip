#ifndef _LOGSTREAM_H_
#define _LOGSTREAM_H_

#include <string>
#define _LOG_FONT_WIDTH_	160
#define _LOG_FONT_HEIGHT_	160

/**
*@brief	ゲーム中でのログの文字列情報クラス
*@details	GameLogクラスでvectorなどでこのオブジェクトを追加していく予定
*/
class LogStream
{
private:
	std::string		m_logStr;	///<	ログで表示させたい1行分文字列
	
	long			m_x;		///<	文字列の基準点X
	long			m_y;		///<	文字列の基準点Y
	unsigned int	m_width;	///<	一文字分の横幅
	unsigned int	m_height;	///<	一文字分の縦幅

public:
	/**
	*@brief	コンストラクタ
	*/
	LogStream( const char* _str, const long _x, const long _y,
		const unsigned int& _width, const unsigned int& _height )
	{
		SetString( _str );
		SetPosition( _x, _y );
		SetSize( _width, _height );
	}

	/**
	*@brief	文字列セット
	*@param[in] _str　セットしたい文字列
	*/
	void SetString( const char* _str )
	{
		m_logStr = _str;
	}

	/**
	*@brief	文字列の一文字のサイズセット
	*@param[in] _width	1文字の横幅
	*@param[in] _height	1文字の縦幅
	*/
	void SetSize( const unsigned int& _width, const unsigned int& _height )
	{
		m_width	= _width;
		m_height= _height;
	}

	/**
	*@brief	文字列の基準点セット
	*@param[in] _x
	*@param[in] _y
	*/
	void SetPosition( const long& _x, const long& _y )
	{
		m_x = _x;
		m_y = _y;
	}

	/**
	*@brief	文字列ポインタ取得
	*/
	std::string* GetStringPtr(){ return &m_logStr; }

	/**
	*@brief	文字列の一文字のサイズ取得
	*@param[out] _width		1文字の横幅
	*@param[out] _height	1文字の縦幅
	*/
	void GetSize( unsigned int& _width, unsigned int& _height)
	{
		_width	= m_width;
		_height	= m_height;
	}

	/**
	*@brief	文字列の基準点取得
	*@param[out] _x
	*@param[out] _y
	*/
	void GetPosition( long& _x, long& _y)
	{
		_x = m_x;
		_y = m_y;
	}

	unsigned int GetHeight(){ return m_height; }

};

#endif