#include "DrawManager.h"

// �`��O����
void CDrawManager::BeginDraw( bool _b3dView )
{
	static bool _SetStateFlag = false;
	if ( !m_pD3Device )
	{

	}
	if( _b3dView || !_SetStateFlag )
	{
		// �X�e�[�W�X�e�[�g�̐ݒ�
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_COLOROP,	D3DTOP_MODULATE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE	);
		
		// �`����@�̐ݒ�
		m_pD3Device -> SetRenderState ( D3DRS_ALPHABLENDENABLE,	true );
		
		m_pD3Device ->  SetRenderState ( D3DRS_SRCBLEND,	D3DBLEND_SRCALPHA	);
		m_pD3Device ->  SetRenderState ( D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA);
		//m_pD3Device ->  SetRenderState ( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1		);

		m_pD3Device -> SetRenderState ( D3DRS_ZENABLE, false );
		_SetStateFlag = true;
	}

	// ��ʂ̏���
	if(	m_pD3Device -> Clear (0, NULL,
							D3DCLEAR_TARGET ,
							D3DCOLOR_XRGB ( 0x00, 0x00, 0x00 ),
							1.0, 0 ) != D3D_OK)
	{
		MessageBoxA(0, "Clear is Fail", NULL,MB_OK );
	}

	// �`��̊J�n
	m_pD3Device -> BeginScene();

	// ��ʂ̕`��
	m_pD3Device -> SetFVF ( D3DFVF_CUSTOMVERTEX );

}

// �e�N�X�`���̓ǂݍ���
// ��1�����F("�摜�̖��O.�g���q"), ��2�����F�e�N�X�`���̔ԍ�, ���ߐFRGB 
bool CDrawManager::LoadTexture ( LPCSTR _lpFileName, int _textuerNumber, int _iColorRed, int _iColorGreen, int _iColorBlue )
{
	// �e�N�X�`�������ɓǂݍ���ł���ꍇ�͂����ŉ������
	if ( FAILED (D3DXCreateTextureFromFileExA (
					m_pD3Device,
					_lpFileName,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_FILTER_NONE,
					D3DCOLOR_ARGB ( 0, _iColorRed, _iColorGreen, _iColorBlue ),
					NULL, NULL,
					&m_TextureInfo [_textuerNumber].pTexture))) {
						MessageBoxA(0,"�e�N�X�`�����ǂݍ��߂܂���ł���(����;)",NULL,MB_OK);
						return false;
	}

	// �e�N�X�`�����擾
	D3DSURFACE_DESC desc;

	m_TextureInfo [_textuerNumber].pTexture -> GetLevelDesc ( 0, &desc );
	m_TextureInfo [_textuerNumber].width = desc.Width;
	m_TextureInfo [_textuerNumber].height = desc.Height;

	

	return true;
}


// �e�N�X�`���̉��
// ��1�����F�e�N�X�`���̔ԍ�
void CDrawManager::ReleaseTexture ( int _textuerNumber )
{
	SAFE_RELEASE ( m_TextureInfo[_textuerNumber].pTexture );
}

// �g�p���Ă���S�Ẵe�N�X�`���̉��
void CDrawManager::ReleaseAllTexture ()
{
	for ( int i = 0; i < _TEXTURE_MAX_; i++ )
	{
		ReleaseTexture (i);
	}
}