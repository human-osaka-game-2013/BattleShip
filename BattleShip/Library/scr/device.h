/**
*@file	device.h
*@author	�T�c
*/
#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "lib_head.h"

/**
*@brief	�f�o�C�X�Ǘ��N���X
*@todo	���̕��������N���X������Ă��Ȃ������ׁA�}篃N���X�ɂ܂Ƃ߂邱�Ƃɂ���B@n
		�e�f�o�C�X���Ƃɔh���N���X��݂����ق���������������Ȃ��B
*/
class CDevice
{
private:
	LPDIRECT3D9				m_pDirect3D;	///<3D�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS	m_d3dpp;		///<�v���[���e�[�V���� �p�����[�^
	LPDIRECT3DDEVICE9		m_pD3Device;	///<D3D�f�o�C�X
	LPDIRECTINPUT8			m_pDinput;		///<�C���v�b�g -> ���͏���
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;	///<�L�[�f�o�C�X -> �O���L�[����
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;	///<�}�E�X�f�o�C�X -> �O���}�E�X����
	HWND*					m_hWnd;			///<�E�C���h�E�n���h��
	
public:
	/**
	*@brief	�R���X�g���N�^
	*@param[in]	_hWnd	�E�C���h�E�n���h��
	*/
	CDevice( HWND* _hWnd );

	/**
	*@brief	�f�X�g���N�^
	*/
	~CDevice();

public:
	/**
	*@brief	�f�o�C�X�N���X�̏�����
	*@details	�e�����o�[�̃f�o�C�X���������܂Ƃ߂�B
	*@return ����������
	*/
	HRESULT	InitDevice();

	/**
	*@brief	 Direct3D�̏�����
	*@return	����������
	*/
	HRESULT InitD3d ();

	/**
	*@brief	 �_�C���N�g�C���v�b�g�̏�����
	*@return	����������
	*/
	HRESULT InitDinput();
	
	/**
	*@brief	�L�[�f�o�C�X�I�u�W�F�N�g�̏�����
	*@return	����������
	*/
	HRESULT InitKeyDevice ();
	
	/**
	*@brief	�}�E�X�f�o�C�X�I�u�W�F�N�g�̏�����
	*@return	����������
	*/
	HRESULT InitMouseDevice ( bool bForeGroundMode = true );
	
	/**
	*@brief	�쐬����DirectX�I�u�W�F�N�g�̊J��
	*@param[in]	_flag
	*/
	void FreeDx(bool _flag);

public:
	/**
	*@brief	D3D�f�o�C�X�̎擾
	*@return	m_pD3Device	
	*/
	LPDIRECT3DDEVICE9	Getd3Device () { return m_pD3Device; }
	
	/**
	*@brief	�C���v�b�g�f�o�C�X�̎擾
	*@return	m_pDinput
	*/
	LPDIRECTINPUT8	GetInputDevice () { return m_pDinput; }
	
	/**
	*@brief	�L�[�f�o�C�X�̎擾
	*@return	m_pKeyDevice
	*/
	LPDIRECTINPUTDEVICE8	GetKeyDevice(){ return m_pKeyDevice; }
	
	/**
	*@brief	�}�E�X�f�o�C�X�̎擾
	*@return	m_pMouseDevice
	*/
	LPDIRECTINPUTDEVICE8	GetMouseDevice(){ return m_pMouseDevice; }

	/**
	*@brief	�E�C���h�E�n���h���擾
	*@return	m_hWnd
	*/
	HWND*	GetWindowHandle(){ return m_hWnd; }

};


#endif

