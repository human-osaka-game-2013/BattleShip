#ifndef _DIRECTXFONT_H_
#define _DIRECTXFONT_H_

#include "lib_head.h"
#include < tchar.h >
#include <tchar.h>

#define _FONT_WIDTH_	16
#define	_FONT_HEIGHT_	16

class DirectXFont
{
	LPD3DXFONT m_font;		///< @brief 描画先フォント
	UINT m_font_heigh;		///< @brief フォントの高さ
	UINT m_font_width;		///< @brief フォントの幅
	
private:

	/** @brief フォントハンドルの解放*/
	void ReleaseFont()
	{
		m_font->Release();
	}

public:
	DirectXFont()
	{
		m_font = NULL;		
		m_font_heigh = _FONT_HEIGHT_;		
		m_font_width = 0;		
	};

	/** @brief メンバ解放*/
	~DirectXFont()
	{
		ReleaseFont();
	}

	/**
	@brief	フォント情報の作成
	@param[ in ] デバイス
	@param[ in ] 作成フォントの高さ
	@param[ in ] 作成フォントの幅
	@param[ in ] 作成フォントの太さ
	@return	true	成功
	@return	false	失敗
	*/
	bool Init(
		const LPDIRECT3DDEVICE9 _dev,
		const UINT _font_heigh = _FONT_HEIGHT_,
		const UINT _font_width = 0
	);

	/**
	@brief	フォントの描画
			第三と四引数で幅を指定しますがこれが小さいと途切れてしまいます
	@param[ in ] フォントの表示X位置
	@param[ in ] フォントの表示Y位置
	@param[ in ] フォントの描画幅
	@param[ in ] フォントの描画高さ
	@param[ in ] 描画文字列
	@param[ in ] フォントのカラー
	@return	true	成功
	@return	false	失敗
	*/
	bool DrawW( 
		LONG _draw_pos_x, LONG _draw_pos_y,
		LONG _w, LONG _h, 
		const LPWSTR _font,
		const D3DXCOLOR *_font_color
	);

	/**
	@brief	フォントの描画
			第三と四引数で幅を指定しますがこれが小さいと途切れてしまいます
	@param[ in ] フォントの表示X位置
	@param[ in ] フォントの表示Y位置
	@param[ in ] フォントの描画幅
	@param[ in ] フォントの描画高さ
	@param[ in ] 描画文字列
	@param[ in ] フォントのカラー
	@param[ in ] 文字列表示フォーマット（デフォルトで左詰め）
	@return	true	成功
	@return	false	失敗
	*/
	bool DrawA( 
		LONG _draw_pos_x,
		LONG _draw_pos_y,
		LONG _w, LONG _h,
		LPCSTR _font,
		const D3DXCOLOR *_font_color = &D3DXCOLOR(0xffffffff),
		unsigned long _format = DT_LEFT
		);

};

#endif