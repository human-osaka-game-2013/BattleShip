#include "device.h"
#include "Mouse.h"

//	�R���X�g���N�^
CMouse::CMouse(IDirectInputDevice8* const _pMouseDevice ): m_pMouseDevice(_pMouseDevice)
{
	for ( int iCount = 0; iCount < MOUSEMAX; iCount++)
	{
		m_mouse[iCount] = OFF;
		m_preMouse[iCount] = false;
	}

	m_moveMouseVol.lMVolX = 0;
	m_moveMouseVol.lMVolY = 0;
	m_moveMouseVol.lMVolZ = 0;

	
	m_poCurrentCursor.x = 0;
	m_poCurrentCursor.y = 0;
	m_poBeforeCursor.x	= 0;
	m_poBeforeCursor.y	= 0;
}

//	�}�E�X��ԃ`�F�b�N
//	����1�F�{�^���̎��
void CMouse::MouseCheck ( int _st )
{
	HRESULT	hr = m_pMouseDevice->Acquire();

	DIMOUSESTATE dims;

	hr = m_pMouseDevice->GetDeviceState(sizeof (dims), &dims);

	if ( hr== S_OK || (hr== S_FALSE) )
	{
		if ( dims.rgbButtons[_st] & 0x80 )
		{
			if ( !m_preMouse[_st] )
			{
				m_mouse[_st] = PUSH;
			}
			else
			{
				m_mouse[_st] = ON;
			}
			m_preMouse[_st] = true;
		}

		else
		{
			if ( !m_preMouse[_st] )
			{
				m_mouse[_st] = OFF;
			}
			else
			{
				m_mouse[_st] = RELEASE;
			}
			m_preMouse[_st] = false;
		}
	}
}

//	�}�E�X�̑S�Ẵ{�^�����`�F�b�N
void CMouse::AllButtonCheck ()
{
	MouseCheck ( MOUSE_L );
	MouseCheck ( MOUSE_R );
	MouseCheck ( MOUSE_C );
}

//	�}�E�X�{�^���ʏ�Ԕ���
//	��1����( �{�^���̎�� )�A��2����( �{�^���̏�� )
bool CMouse::MouseStCheck ( int _st, int _mouseSt )
{
	return	 m_mouse[_st] == _mouseSt ? true : false ;
}

//	�}�E�X���W�̎擾�Ɩ��t���[���Ԃ̈ړ��ʂ��X�V�B
//	����1�F�E�C���h�E�n���h��
void CMouse::CursorSet(HWND* hWnd)
{
	GetCursorPos( &m_poCurrentCursor );

	ScreenToClient( *hWnd, &m_poCurrentCursor );

	m_moveMouseVol.lMVolX = m_poCurrentCursor.x - m_poBeforeCursor.x;
	m_moveMouseVol.lMVolY = m_poCurrentCursor.y - m_poBeforeCursor.y;

	m_poBeforeCursor = m_poCurrentCursor;	
}

/*
	�f�X�g���N�^
*/
CMouse::~CMouse()
{

}