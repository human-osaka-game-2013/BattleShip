#ifndef _DIRECTXFONT_H_
#define _DIRECTXFONT_H_

#include "lib_head.h"
#include < tchar.h >
#include <tchar.h>

#define _FONT_WIDTH_	16
#define	_FONT_HEIGHT_	16

class DirectXFont
{
	LPD3DXFONT m_font;		///< @brief �`���t�H���g
	UINT m_font_heigh;		///< @brief �t�H���g�̍���
	UINT m_font_width;		///< @brief �t�H���g�̕�
	
private:

	/** @brief �t�H���g�n���h���̉��*/
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

	/** @brief �����o���*/
	~DirectXFont()
	{
		ReleaseFont();
	}

	/**
	@brief	�t�H���g���̍쐬
	@param[ in ] �f�o�C�X
	@param[ in ] �쐬�t�H���g�̍���
	@param[ in ] �쐬�t�H���g�̕�
	@param[ in ] �쐬�t�H���g�̑���
	@return	true	����
	@return	false	���s
	*/
	bool Init(
		const LPDIRECT3DDEVICE9 _dev,
		const UINT _font_heigh = _FONT_HEIGHT_,
		const UINT _font_width = 0
	);

	/**
	@brief	�t�H���g�̕`��
			��O�Ǝl�����ŕ����w�肵�܂������ꂪ�������Ɠr�؂�Ă��܂��܂�
	@param[ in ] �t�H���g�̕\��X�ʒu
	@param[ in ] �t�H���g�̕\��Y�ʒu
	@param[ in ] �t�H���g�̕`�敝
	@param[ in ] �t�H���g�̕`�捂��
	@param[ in ] �`�敶����
	@param[ in ] �t�H���g�̃J���[
	@return	true	����
	@return	false	���s
	*/
	bool DrawW( 
		LONG _draw_pos_x, LONG _draw_pos_y,
		LONG _w, LONG _h, 
		const LPWSTR _font,
		const D3DXCOLOR *_font_color
	);

	/**
	@brief	�t�H���g�̕`��
			��O�Ǝl�����ŕ����w�肵�܂������ꂪ�������Ɠr�؂�Ă��܂��܂�
	@param[ in ] �t�H���g�̕\��X�ʒu
	@param[ in ] �t�H���g�̕\��Y�ʒu
	@param[ in ] �t�H���g�̕`�敝
	@param[ in ] �t�H���g�̕`�捂��
	@param[ in ] �`�敶����
	@param[ in ] �t�H���g�̃J���[
	@param[ in ] ������\���t�H�[�}�b�g�i�f�t�H���g�ō��l�߁j
	@return	true	����
	@return	false	���s
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