#ifndef	_GAMELOG_H_
#define _GAMELOG_H_
#include <list>
#include "StageDefineList.h"
#include "LogStream.h"
#include "FixedPhrase.h"

#define _LOG_HEIGHT_MAX_	_BLOCK_HEIGHT_SIZE_*5 -_LOG_POS_TWEAK_-_LOG_FONT_HEIGHT_///<ログボックスの縦幅
#define _LOG_POS_TWEAK_		8.0f	///<ログテキストを表示する際の座標微調整の定数
#define _LOG_COLOR_DEFAULT_		0xFFFFFFFF	///<ログテキストを表示する際のデフォルトカラー値	
#define _LOG_COLOR_WARNING_		0xFFFF0000	///<ゲーム内での警告系ログを表示する際のカラー
#define _LOG_COLOR_SUCCESS_		0xFF00FF00	///<ゲーム内でのプレイヤーに優位的なログを表示する際のカラー
#define _LOG_COLOR_NOMAL_		0xFF0000FF	

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

//	ログに表示させる文字の定型文字列
public:
	const FixedPhrase m_fixedPhrase;

public:
	/**
	*@brief	コンストラクタ
	*@details	念のためパラメータなどを0で初期化
	*/
	GameLog()
	{
		SetPosition( 0, 0 );
	}

	/**
	*@breif	デストラクタ
	*/
	~GameLog()
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

	/**
	*@brief	初期化
	*@details	ログの表示基準座標xyならびに、最初に追加したい文字列があれば、ここで追加する事も出来る。
				文字列はデフォルトでNULLなので、追加しないならDirectXFontクラスを用いて描画する場合に必要な情報は渡せないので注意。
	*/
	void Init( const long& _x, const long& _y, const char* _firstStr = NULL );


	/**
	*@brief	文字列の追加
	*@param[in] _str	追加したい文字列
	*@param[in] _color	デフォルトでは
	*@param[in] _width	デフォルトでは定数宣言したフォントサイズを使う	
	*@param[in] _height	デフォルトでは定数宣言したフォントサイズを使う
	*/
	void AddStream( const char* _str, const D3DXCOLOR& _color = _LOG_COLOR_DEFAULT_ , const unsigned int _width = _LOG_FONT_WIDTH_, const unsigned int _height = _LOG_FONT_HEIGHT_ );

	/**
	*@brief	登録している文字列の縦幅をチェック
	*@details	登録している文字列の縦幅を加算していき、
				指定した数値以上にだった場合は後に登録していたものから削除していく
	*@param[in]	_height	比較したい縦幅サイズ
	*/
	bool CheckStream( const unsigned int _height );

	/**
	*@brief	ログの再配置
	*@details	ログ内の文字を消しても描画座標などは変わってないので、
				残された文字列の描画座標の再計算をしてやる必要がある。
	*/
	void RealignmentStream();

	/**
	*@brief	定型文字列を複数繋ぎあわせて送る関数
	*@param[in]	つなげる定型分の量
	*/
	const std::string GetMultiplePhrase( int _phraseVal,... );

	void SetPosition( const long& _x, const long& _y )
	{
		m_posX = _x;
		m_posY = _y;
	}

	void GetPosition( long& _x, long& _y )
	{
		_x = m_posX;
		_y = m_posY;
	}

	/**
	*@brief
	*/
	std::string GetPhrase( FixedPhrase::_PHRASE_STR_TYPE_ _phraseType )
	{
		return m_fixedPhrase.m_phrase[ _phraseType ];
	}
};


#endif