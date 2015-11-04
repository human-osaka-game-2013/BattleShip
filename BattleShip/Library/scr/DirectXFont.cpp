#include "DirectXFont.h"

/**
@brief	�t�H���g���̍쐬
@param[ in ] �f�o�C�X
@param[ in ] �쐬�t�H���g�̍���
@param[ in ] �쐬�t�H���g�̕�
@param[ in ] �쐬�t�H���g�̑���
@return	true	����
@return	false	���s
*/
bool DirectXFont::Init(
	const LPDIRECT3DDEVICE9 _dev,
	const UINT _font_heigh,
	const UINT _font_width,
	const UINT _font_thickness
) 
{
	//�f�o�C�X�������Ȃ�쐬�s�\
	if( _dev == NULL ){return false;}
	
	//���łɊm�ۂ���Ă���Ȃ������Ă�����s
	if( m_font != NULL ){ ReleaseFont(); }

	//�쐬�^�C�v�̍X�V
	m_font_heigh = _font_heigh;
	m_font_width = _font_width;
	m_font_thickness  = _font_thickness;

	//�쐬�J�n
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

	//����
	return true;
}

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
bool DirectXFont::DrawW( 
	LONG _draw_pos_x,
	LONG _draw_pos_y,
	LONG _w, LONG _h,
	const LPWSTR _font,
	const D3DXCOLOR *_font_color
	)
{
	//�t�H���g�n���h��������
	if( m_font == NULL ){ return false; }

	//�\���ꏊ(�͈�)
	RECT rec ={ _draw_pos_x, _draw_pos_y, _w, _h };

	//�����\��
	m_font->DrawTextW(
		NULL,
		_font,
		-1,
		&rec,
		DT_LEFT,
		( *_font_color )
		);
	
	//����
	return true;
}

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
bool DirectXFont::DrawA( 
	LONG _draw_pos_x,
	LONG _draw_pos_y,
	LONG _w, LONG _h,
	LPCSTR _font,
	const D3DXCOLOR *_font_color
	)
{
	//�t�H���g�n���h��������
	if( m_font == NULL ){ return false; }

	//�\���ꏊ(�͈�)
	RECT rec ={ _draw_pos_x, _draw_pos_y, _w, _h };
	
	//�����\��
	m_font->DrawTextA(
		NULL,
		_font,
		-1,
		&rec,
		DT_LEFT,
		( *_font_color )
		);
	
	//����
	return true;
}