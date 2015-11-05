/**
*@file	device.h
*@author	亀田
*/
#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "lib_head.h"

/**
*@brief	デバイス管理クラス
*@todo	この部分だけクラス化されていなかった為、急遽クラスにまとめることにする。@n
		各デバイスごとに派生クラスを設けたほうがいいかもしれない。
*/
class CDevice
{
private:
	LPDIRECT3D9				m_pDirect3D;	///<3Dオブジェクト
	D3DPRESENT_PARAMETERS	m_d3dpp;		///<プレゼンテーション パラメータ
	LPDIRECT3DDEVICE9		m_pD3Device;	///<D3Dデバイス
	LPDIRECTINPUT8			m_pDinput;		///<インプット -> 入力処理
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;	///<キーデバイス -> 外部キー入力
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;	///<マウスデバイス -> 外部マウス入力
	HWND*					m_hWnd;			///<ウインドウハンドル
	
public:
	/**
	*@brief	コンストラクタ
	*@param[in]	_hWnd	ウインドウハンドル
	*/
	CDevice( HWND* _hWnd );

	/**
	*@brief	デストラクタ
	*/
	~CDevice();

public:
	/**
	*@brief	デバイスクラスの初期化
	*@details	各メンバーのデバイス初期化をまとめる。
	*@return 初期化結果
	*/
	HRESULT	InitDevice();

	/**
	*@brief	 Direct3Dの初期化
	*@return	初期化結果
	*/
	HRESULT InitD3d ();

	/**
	*@brief	 ダイレクトインプットの初期化
	*@return	初期化結果
	*/
	HRESULT InitDinput();
	
	/**
	*@brief	キーデバイスオブジェクトの初期化
	*@return	初期化結果
	*/
	HRESULT InitKeyDevice ();
	
	/**
	*@brief	マウスデバイスオブジェクトの初期化
	*@return	初期化結果
	*/
	HRESULT InitMouseDevice ( bool bForeGroundMode = true );
	
	/**
	*@brief	作成したDirectXオブジェクトの開放
	*@param[in]	_flag
	*/
	void FreeDx(bool _flag);

public:
	/**
	*@brief	D3Dデバイスの取得
	*@return	m_pD3Device	
	*/
	LPDIRECT3DDEVICE9	Getd3Device () { return m_pD3Device; }
	
	/**
	*@brief	インプットデバイスの取得
	*@return	m_pDinput
	*/
	LPDIRECTINPUT8	GetInputDevice () { return m_pDinput; }
	
	/**
	*@brief	キーデバイスの取得
	*@return	m_pKeyDevice
	*/
	LPDIRECTINPUTDEVICE8	GetKeyDevice(){ return m_pKeyDevice; }
	
	/**
	*@brief	マウスデバイスの取得
	*@return	m_pMouseDevice
	*/
	LPDIRECTINPUTDEVICE8	GetMouseDevice(){ return m_pMouseDevice; }

	/**
	*@brief	ウインドウハンドル取得
	*@return	m_hWnd
	*/
	HWND*	GetWindowHandle(){ return m_hWnd; }

};


#endif

