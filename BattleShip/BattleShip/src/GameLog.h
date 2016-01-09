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
#define _LOG_COLOR_NOMAL_		0xFF00A0FF		
#define _LOG_COLOR_PHASE_		0xFFFFFF00

/**
*@brief	ゲーム中に表示させるログクラス
*/
class GameLog {
 public:
	/**
	*@brief	コンストラクタ
	*@details	念のためパラメータなどを0で初期化
	*/
	GameLog() {
		SetPosition( 0, 0 );
	}

	/**
	*@breif	デストラクタ
	*/
	~GameLog() {
		//	要素が空で無かったら
		if (!m_logStream.empty()) {
			//	要素の解放および削除
			std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
			for ( std::list<LogStream*>::iterator it = m_logStream.begin(); it != itEnd; ++it ) {
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
	void Init( const long& _x, const long& _y, const char* _firstStr = "", const D3DXCOLOR& _color = _LOG_COLOR_DEFAULT_ );

	/**
	*@brief	文字列の追加
	*@param[in] _str	追加したい文字列
	*@param[in] _color	デフォルトでは
	*@param[in] _width	デフォルトでは定数宣言したフォントサイズを使う	
	*@param[in] _height	デフォルトでは定数宣言したフォントサイズを使う
	*@param[in] _format	追加した文字列を表示する際のフォーマット（DrawText関数依存）
	*/
	void AddStream( const char* _str,const D3DXCOLOR& _color = _LOG_COLOR_DEFAULT_ ,
					const unsigned int _width = _LOG_FONT_WIDTH_,
					const unsigned int _height = _LOG_FONT_HEIGHT_,
					unsigned long _format = DT_LEFT );

	/**
	*@brief	定型文字列を複数繋ぎあわせて送る関数
	*@param[in]	つなげる定型分の量
	*/
	const std::string GetMultiplePhrase( int _phraseVal,... );

	inline void SetPosition( const long& _x, const long& _y ) {
		m_posX = _x;
		m_posY = _y;
	}

	inline void GetPosition( long& _x, long& _y ) {
		_x = m_posX;
		_y = m_posY;
	}

	/**
	*@brief	定型文の文字列を取得
	*/
	std::string GetPhrase( FixedPhrase::_PHRASE_STR_TYPE_ _phraseType ) {
		return m_fixedPhrase.m_phrase[ _phraseType ];
	}

	/**
	*@brief	文字列の削除
	*@param[in]	_deleteType	true：前から消す、false：後から消す
	*/
	void DeleteStream( bool _deleteType = true ) {
		if (_deleteType) {
			std::list<LogStream*>::iterator it = m_logStream.begin();
			delete *it;
			m_logStream.pop_front();
		}else {
			LogStream* tempList = m_logStream.back();
			delete tempList;
			m_logStream.pop_back();
		}
	}

	/**
	*@brief	文字列の削除
	*@details	ログはリスト型なので、整列させる必要があるので文字列の幅を取得
	*@param[out]_height	削除した文字列の幅を取得
	*@param[in]	_deleteType	true：前から消す、false：後から消す
	*/
	void DeleteStream( int& _height, bool _deleteType = true ) {
		std::list<LogStream*>::iterator it = m_logStream.begin();
		_height = (*it)->GetHeight();
		delete *it;
		m_logStream.pop_front();
	}

	std::list<LogStream*> m_logStream;	///< listのアクセス＞安全性というコスト判断をしたので、publicです。
	const FixedPhrase m_fixedPhrase; ///<	ログに表示させる文字の定型文字列
	
 private:	
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

	long m_posX;	///< ログの基準となるX座標
	long m_posY;	///< ログの基準となるY座標

};


#endif