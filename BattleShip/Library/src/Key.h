

#ifndef	_KEY_H_
#define _KEY_H_

#include "Input.h"
#include "device.h"

/**
*@brief	使用するキーの種類
*@details	KeyCheckと共に使うキーが増えればココに種類を追加していく
*/ 
enum eKEYKIND
{
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	COMMA,
	
	ENTER,

	KEYMAX
};

/**
*@brief	キーの状態管理クラス
*/
class CKey
{
private:
	int m_key[KEYMAX];		///< キーの状態を種類別に格納する変数
	bool m_preKey[KEYMAX];	///< キーの種類別に押されているかのフラグ
	IDirectInputDevice8* const	m_pKeyDevice;	///<	キーデバイスオブジェクトのポインタ

public:
	/**
	*@brief	コンストラクタ
	*@param[in]
	*/
	CKey( IDirectInputDevice8* const _pKeyDevice);

public:
	/**
	*@brief	キー状態チェック
	*@param[in]	_dik	キーの定数
	*@param[in]	_st		キーの種類
	*/
	void KeyCheck ( int _dik, int _st );

	/**
	*@brief	複数のキーの状態をまとめてチェック
	*@details	KeyCheck関数をまとめて呼び出す
	*/
	void AllKeyCheck ();
	
	/**
	*@brief	キー状態チェック
	*@param[in]	_st		キーの種類
	*@param[in]	_keySt	キーの状態
	*/
	bool StCheck(int _st, int _keySt);

};
#endif