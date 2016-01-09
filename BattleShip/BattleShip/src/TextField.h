#ifndef _TEXTFIELD_H_
#define _TEXTFIELD_H_

#include "LogStream.h"
#include <cstdio>
/**
*@brief	テキストフィールドクラス
*@details	現在は0～9+,に対応
*/
class TextField {
 public:
	/**
	*@brief	コンストラクタ

	*/
	TextField(  const char* _str,
				const long _x,const long _y,
				const float _width,const float _height,
				const unsigned int& _text_w = _LOG_FONT_WIDTH_,
				const unsigned int& _text_h = _LOG_FONT_HEIGHT_ ) 
				: m_str( _str, _x, _y, _text_w, _text_h),  fWidth(_width), fHeight(_height) {
	
		m_settingFlag = false;
	}

	/**
	*@brief	文字列の追加（結合）
	*/
	void AddStr( const char* _str ) {
		m_str.AppendStr(_str);
	}
	/**
	*@brief	文字列の追加
	*details	数値を文字列に変換してから追加Ver
	*/
	void AddStr( int _num ) {
		const unsigned char _word = ConvertNumFromWord(_num);
		char temp[2];
		sprintf_s( temp, "%c", _word );
		AddStr( temp );
	}

	/**
	*@brief	文字列のリセット（全消去）
	*/
	void ResetStr() {
		m_str.DeleteStr();
	}
	
	/**
	*@brief	テキストフィールドの選択チェック
	*details	イベントが起きた際（マウスが押された時など）に指定座標と、
				自身のテキストフィールド内に指定座標が接触しているかを判定。\n
				現在は選択された時点で一度登録されている文字列を初期化

	*/
	bool SelectCheck( float _x, float _y ) {
		long tempX, tempY;
		bool result = false;
		m_str.GetPosition( tempX, tempY );

		if (tempX < static_cast<long>(_x) && tempX + fWidth > static_cast<long>(_x)) {
			if (tempY < static_cast<long>(_y) && tempY + fHeight > static_cast<long>(_y)) {
				m_settingFlag = true;
				ResetStr();	///< 選択中になったら一度
				return m_settingFlag;
			}
		}
		m_settingFlag = false;
		return m_settingFlag;
	}

	bool	m_settingFlag;	///<	入力受付中フラグ
	LogStream m_str;		///<	入力情報格納文字列クラス
	float fWidth ,fHeight;	///<	テキストフィールド自体の幅高さ

 private:
	/**
	*@brief	数値を文字へ変換
	*details	どのような文字コードへ変換するかは独自に必要に応じて追加してください。\n
				基本的にAddStr関数と併用する形にしてください。
	*@return	変換した文字の1バイトデータ
	*/
	const unsigned char ConvertNumFromWord( int _num );

};

#endif