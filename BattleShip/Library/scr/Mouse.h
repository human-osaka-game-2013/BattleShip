
#ifndef	_MOUSE_H_
#define _MOUSE_H_

#include"Input.h"

/**
*@brief	マウスボタンの列挙
*/
enum eMOUSEKIND
{
	MOUSE_L,
	MOUSE_R,
	MOUSE_C,
	
	MOUSEMAX
};

/**
*@brief	マウス座標構造体
*@details	D3DXVECTOR3だとマウス座標取得に用意されているPOINT構造体との、@n
			型が違うため、自前で用意している。
*/
struct	MOUSE_VOL
{
	long	lMVolX, lMVolY, lMVolZ;
};

/**
*@brief	マウスクラス
*/
class CMouse
{
private:
	int		m_mouse[MOUSEMAX];	///<	マウスの状態を種類別に格納する変数
	bool	m_preMouse[MOUSEMAX];	///<	マウスの種類別に押されているかのフラグ

	POINT	m_poCurrentCursor;	///<	現在のマウス座標
	POINT	m_poBeforeCursor;	///<	前のマウス座標
	MOUSE_VOL	m_moveMouseVol;	///<	マウスの移動量

	IDirectInputDevice8* const	m_pMouseDevice;	///<	キーデバイスオブジェクトのポインタ

public:
	/**
	*@brief	コンストラクタ
	*@details	メンバ変数などの初期化程度
	*/
	CMouse( IDirectInputDevice8* const _pMouseDevice );	
	/**
	*@brief	デストラクタ
	*/
	~CMouse();	

public:
	
	/**
	*@brief	マウス座標の取得X
	*/
	long GetCursorPosX () { return m_poCurrentCursor.x; }
	/**
	*@brief	マウス座標の取得Y
	*/
	long GetCursorPosY () { return m_poCurrentCursor.y; }
	/**
	*@brief	マウス移動量の取得X
	*/
	long GetCursorMoveVolX () { return m_moveMouseVol.lMVolX; }
	/**
	*@brief	マウス移動量の取得Y
	*/
	long GetCursorMoveVolY () { return m_moveMouseVol.lMVolY; }
	
	/**
	*@brief	マウス状態チェック
	*/
	void MouseCheck ( int st );

	void AllButtonCheck ();	//	マウスの全てのボタンをチェック
	
	/**
	*@brief	マウスボタン別状態判定
	*@param[in]	_st	ボタンの種類
	ボタンの状態 )
	*/
	bool MouseStCheck ( int _st, int MouseSt );

	//	マウス座標の取得と毎フレーム間の移動量を更新。
	//	引数1：ウインドウハンドル
	void CursorSet(HWND hWnd);

};

#endif