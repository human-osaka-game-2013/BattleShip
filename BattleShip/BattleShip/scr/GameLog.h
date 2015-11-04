#ifndef	_GAMELOG_H_
#define _GAMELOG_H_
#include <list>
#include "StageDefineList.h"
#include "LogStream.h"

#define _LOG_HEIGHT_MAX_	_BLOCK_HEIGHT_SIZE_*5	///<ログボックスの縦幅

/**
*@brief	ゲーム中に表示させるログクラス
*/
class GameLog
{
public:
	std::list<LogStream*> m_logStream;	///< listのアクセス＞安全性というコスト判断をしたので、publicです。
private:
	long m_posX;	///< ログの基準となるX座標
	long m_posY;	///< ログの基準となるY座標

public:
	GameLog()
	{
		SetPosition( 0, 0 );
	}
	/**
	*@breif	デストラクタ
	*/
	~GameLog()
	{
		Free();
	}


	/**
	*@brief	文字列の追加
	*@param[in] _str	追加したい文字列
	*@param[in] _width	デフォルトでは定数宣言したフォントサイズを使う	
	*@param[in] _height	デフォルトでは定数宣言したフォントサイズを使う
	*/
	void AddStream( const char* _str, const unsigned int _width = _LOG_FONT_WIDTH_, const unsigned int _height = _LOG_FONT_HEIGHT_ );

	/**
	*@brief	登録している文字列の縦幅をチェック
	*@details	登録している文字列の縦幅を加算していき、
				指定した数値以上にだった場合は後に登録していたものから削除していく
	*@param[in]	_height	比較したい縦幅サイズ
	*/
	bool CheckStream( const unsigned int _height );

	void GetPosition( long& _x, long& _y )
	{
		_x = m_posX;
		_y = m_posY;
	}

	void SetPosition( const long& _x, const long& _y )
	{
		m_posX = _x;
		m_posY = _y;
	}

	/**
	*@brief	全要素解放
	*/
	void Free()
	{
		//	要素が空で無かったら
		if( !m_logStream.empty() ){
			//	要素の解放および削除
			std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
			for( std::list<LogStream*>::iterator it = m_logStream.begin();
				it != itEnd; ++it)
			{
				delete *it;	///< 中身を解放
			}
			m_logStream.clear();	///< listの全削除
		}
	}
};


#endif