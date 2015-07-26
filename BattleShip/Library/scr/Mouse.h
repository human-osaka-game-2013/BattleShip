
#ifndef	_MOUSE_H_
#define _MOUSE_H_

#include"Input.h"

/**
*@brief	�}�E�X�{�^���̗�
*/
enum eMOUSEKIND
{
	MOUSE_L,
	MOUSE_R,
	MOUSE_C,
	
	MOUSEMAX
};

/**
*@brief	�}�E�X���W�\����
*@details	D3DXVECTOR3���ƃ}�E�X���W�擾�ɗp�ӂ���Ă���POINT�\���̂Ƃ́A@n
			�^���Ⴄ���߁A���O�ŗp�ӂ��Ă���B
*/
struct	MOUSE_VOL
{
	long	lMVolX, lMVolY, lMVolZ;
};

/**
*@brief	�}�E�X�N���X
*/
class CMouse
{
private:
	int		m_mouse[MOUSEMAX];	///<	�}�E�X�̏�Ԃ���ޕʂɊi�[����ϐ�
	bool	m_preMouse[MOUSEMAX];	///<	�}�E�X�̎�ޕʂɉ�����Ă��邩�̃t���O

	POINT	m_poCurrentCursor;	///<	���݂̃}�E�X���W
	POINT	m_poBeforeCursor;	///<	�O�̃}�E�X���W
	MOUSE_VOL	m_moveMouseVol;	///<	�}�E�X�̈ړ���

	IDirectInputDevice8* const	m_pMouseDevice;	///<	�L�[�f�o�C�X�I�u�W�F�N�g�̃|�C���^

public:
	/**
	*@brief	�R���X�g���N�^
	*@details	�����o�ϐ��Ȃǂ̏��������x
	*/
	CMouse( IDirectInputDevice8* const _pMouseDevice );	
	/**
	*@brief	�f�X�g���N�^
	*/
	~CMouse();	

public:
	
	/**
	*@brief	�}�E�X���W�̎擾X
	*/
	long GetCursorPosX () { return m_poCurrentCursor.x; }
	/**
	*@brief	�}�E�X���W�̎擾Y
	*/
	long GetCursorPosY () { return m_poCurrentCursor.y; }
	/**
	*@brief	�}�E�X�ړ��ʂ̎擾X
	*/
	long GetCursorMoveVolX () { return m_moveMouseVol.lMVolX; }
	/**
	*@brief	�}�E�X�ړ��ʂ̎擾Y
	*/
	long GetCursorMoveVolY () { return m_moveMouseVol.lMVolY; }
	
	/**
	*@brief	�}�E�X��ԃ`�F�b�N
	*/
	void MouseCheck ( int st );

	void AllButtonCheck ();	//	�}�E�X�̑S�Ẵ{�^�����`�F�b�N
	
	/**
	*@brief	�}�E�X�{�^���ʏ�Ԕ���
	*@param[in]	_st	�{�^���̎��
	�{�^���̏�� )
	*/
	bool MouseStCheck ( int _st, int MouseSt );

	//	�}�E�X���W�̎擾�Ɩ��t���[���Ԃ̈ړ��ʂ��X�V�B
	//	����1�F�E�C���h�E�n���h��
	void CursorSet(HWND hWnd);

};

#endif