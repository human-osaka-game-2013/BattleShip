#include "DirectXFont.h"

/**
@brief	フォント情報の作成
@param[ in ] デバイス
@param[ in ] 作成フォントの高さ
@param[ in ] 作成フォントの幅
@param[ in ] 作成フォントの太さ
@return	true	成功
@return	false	失敗
*/
bool DirectXFont::Init(
	const LPDIRECT3DDEVICE9 _dev,
	const UINT _font_heigh,
	const UINT _font_width,
	const UINT _font_thickness
) 
{
	//デバイスが無いなら作成不可能
	if( _dev == NULL ){return false;}
	
	//すでに確保されているなら解放してから実行
	if( m_font != NULL ){ ReleaseFont(); }

	//作成タイプの更新
	m_font_heigh = _font_heigh;
	m_font_width = _font_width;
	m_font_thickness  = _font_thickness;

	//作成開始
	D3DXCreateFont(
		_dev,
		m_font_heigh,
		m_font_width,
		m_font_thickness,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		NULL,
		&m_font
	);

	//成功
	return true;
}

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
bool DirectXFont::DrawW( 
	LONG _draw_pos_x,
	LONG _draw_pos_y,
	LONG _w, LONG _h,
	const LPWSTR _font,
	const D3DXCOLOR *_font_color
	)
{
	//フォントハンドルが無い
	if( m_font == NULL ){ return false; }

	//表示場所(範囲)
	RECT rec ={ _draw_pos_x, _draw_pos_y, _w, _h };

	//文字表示
	m_font->DrawTextW(
		NULL,
		_font,
		-1,
		&rec,
		DT_LEFT,
		( *_font_color )
		);
	
	//成功
	return true;
}

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
bool DirectXFont::DrawA( 
	LONG _draw_pos_x,
	LONG _draw_pos_y,
	LONG _w, LONG _h,
	LPCSTR _font,
	const D3DXCOLOR *_font_color
	)
{
	//フォントハンドルが無い
	if( m_font == NULL ){ return false; }

	//表示場所(範囲)
	RECT rec ={ _draw_pos_x, _draw_pos_y, _w, _h };
	
	//文字表示
	m_font->DrawTextA(
		NULL,
		_font,
		-1,
		&rec,
		DT_LEFT,
		( *_font_color )
		);
	
	//成功
	return true;
}