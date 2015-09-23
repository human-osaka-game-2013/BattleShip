#include "device.h"
#include "joystick_XInput.h"

//	�R���X�g���N�^
CDevice::CDevice( HWND* _hWnd ) : m_hWnd(_hWnd)
{

}

HRESULT	CDevice::InitDevice()
{
	// Direct3D����̏���������
	if ( FAILED ( InitD3d() ) ) return 0;
	
	//	�L�[�̏�����
	if ( FAILED ( InitDinput() ) ) return 0;

	return 1;
}

// Direct3D�̏�����
// ��1�����F�E�C���h�n���h��
HRESULT CDevice::InitD3d ()
{
	D3DDISPLAYMODE d3ddm;
	
	// DirectX �I�u�W�F�N�g�̐���
	if( NULL == ( m_pDirect3D = Direct3DCreate9 ( D3D_SDK_VERSION ) ) )
	{
		MessageBoxA(0,"Direct3D�̍쐬�Ɏ��s���܂���","",MB_OK);
		return E_FAIL;
	}

	// Display Mode �̐ݒ�
	m_pDirect3D -> GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory(	&m_d3dpp, sizeof ( m_d3dpp ));

	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.BackBufferCount  = 1;
	m_d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.Windowed		   = TRUE;

	if( FAILED( m_pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
										 D3DDEVTYPE_HAL,
										 *m_hWnd,
										 D3DCREATE_HARDWARE_VERTEXPROCESSING,
										 &m_d3dpp,
										 &m_pD3Device ) ) )
	{
		MessageBoxA(0,"HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�",NULL,MB_OK);
		if( FAILED( m_pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
											 D3DDEVTYPE_REF,
											 *m_hWnd,
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											 &m_d3dpp,
											 &m_pD3Device ) ) )
		{
			MessageBoxA(0,"DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���",NULL,MB_OK);
				return E_FAIL;
		}    
	}

	return S_OK;
}

//�_�C���N�g�C���v�b�g�̏������֐�
HRESULT CDevice::InitDinput()
{
	HRESULT hr;
	
	//�DirectInput��I�u�W�F�N�g�̍쐬
	if(FAILED (hr = DirectInput8Create ( GetModuleHandle(NULL),
										 DIRECTINPUT_VERSION,
										 IID_IDirectInput8,
										 (VOID**)&m_pDinput,
										 NULL ) ) )
	{
		return hr;
	}
	//	�L�[�{�[�h�f�o�C�X�̃I�u�W�F�N�g�̍쐬
	if (FAILED (hr = InitKeyDevice () ) )
	{
		return hr;
	}
	
	//	�}�E�X�f�o�C�X�̃I�u�W�F�N�g�̍쐬
	if (FAILED (hr = InitMouseDevice ( false ) ) )
	{
		return hr;
	}	

	return S_OK;
}


// �L�[�f�o�C�X�I�u�W�F�N�g�̏�����
HRESULT CDevice::InitKeyDevice ()
{
	HRESULT hr;
	
	//�DirectInput�f�o�C�X��I�u�W�F�N�g�̍쐬(�L�[�{�[�h)
	if(FAILED (hr = m_pDinput->CreateDevice (	GUID_SysKeyboard,
											&m_pKeyDevice,
											NULL ) ) )
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	if(FAILED (hr = m_pKeyDevice->SetDataFormat (&c_dfDIKeyboard) ) )
	{
		return hr;
	}
	//�������x���̐ݒ�		*���Y�A�v���P�[�V����(�Q�[��)�ƁAwindowsOS���̂̃L�[�{�[�h�f�o�C�X�̐�L���ݒ�
	if(FAILED (hr = m_pKeyDevice->SetCooperativeLevel( *m_hWnd,
													 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )	// * ��r���Ńo�b�N�E�O���E���h
	{
		return hr;
	}
	//�f�o�C�X��擾�����
	m_pKeyDevice->Acquire();	// * �쐬�����f�o�C�X�ւ̃A�N�Z�X���擾
	
	return S_OK;
}

//-----------------------------------------------------------------------------
// �}�E�X�p�I�u�W�F�N�g�쐬
//-----------------------------------------------------------------------------
HRESULT CDevice::InitMouseDevice ( bool bForeGroundMode )
{
	HRESULT hr;
	LPDIENUMDEVICESCALLBACK lpCallback	= NULL;
	LPVOID	pvRef	= NULL;		
	HGLOBAL	hGlobal	= NULL;	//	�O���[�o���n���h��	
	
	//�DirectInput�f�o�C�X��I�u�W�F�N�g�̍쐬(�}�E�X)
	if(FAILED (hr = m_pDinput->CreateDevice ( GUID_SysMouseEm,
											&m_pMouseDevice,
											NULL ) ) )
	{
		return hr;
	}

	//�f�o�C�X���}�E�X�ɐݒ�
	if(FAILED (hr = m_pMouseDevice->SetDataFormat (&c_dfDIMouse) ) )
	{
		return hr;
	}

	if ( bForeGroundMode )	// �t�H�A�O���E���h�Ń}�E�X���g���Ȃ�
	{
		//	�}�E�X�̓���̐ݒ�
		if(FAILED (hr = m_pMouseDevice->SetCooperativeLevel( *m_hWnd,
														   DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
		{
			return hr;
		}
	}
	else
	{
		//	�}�E�X�̓���̐ݒ�
		if(FAILED (hr = m_pMouseDevice->SetCooperativeLevel( *m_hWnd,
														   DISCL_EXCLUSIVE | DISCL_BACKGROUND ) ) )
		{
			/*return hr;*/
		}
	}

	//	�C�x���g�ʒm���g���ă}�E�X�̓�������o������@�ƁA
	//	�}�E�X����̃o�b�t�@�����O���͂�ǂݎ��
	hGlobal = CreateEvent(NULL, FALSE, FALSE, NULL);

	if( hGlobal == NULL )
	{
		return FALSE;
	}
	//	�f�o�C�X��Ԃ��ω������Ƃ��ɐݒ肳���C�x���g���w�肷��
	if (FAILED ( hr = m_pMouseDevice->SetEventNotification ( hGlobal ) ) )
	{
		return hr;
	}

	DIPROPDWORD dipdw;
    // the header
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    // the data
    dipdw.dwData            = DIPROPAXISMODE_REL;

	//	�f�o�C�X�̓�����`����v���p�e�B��ݒ肷��
	if (FAILED ( hr = m_pMouseDevice->SetProperty( DIPROP_BUFFERSIZE,
												 &dipdw.diph ) ) )
	{
		return hr;
	}

	//�f�o�C�X��擾�����
	m_pMouseDevice->Acquire();	// * �쐬�����f�o�C�X�ւ̃A�N�Z�X���擾
	
	return S_OK;
}

/*
	�f�X�g���N�^
*/
CDevice::~CDevice()
{
	FreeDx( true );
}

// �쐬����DirectX�I�u�W�F�N�g�̊J��
//
void CDevice::FreeDx(bool _flag)
{		
	//	�L�[�f�o�C�X�̉��
	if( m_pKeyDevice ) 
	{
		m_pKeyDevice->Unacquire();
	}
	//	�}�E�X�f�o�C�X�̉��
	if( m_pMouseDevice ) 
	{
		m_pMouseDevice->Unacquire();
	}
	
	SAFE_RELEASE( m_pKeyDevice );
	SAFE_RELEASE( m_pMouseDevice );
	SAFE_RELEASE( m_pDinput );

	if(_flag)
	{
		SAFE_RELEASE( m_pDirect3D );
		SAFE_RELEASE( m_pD3Device );
	}
}