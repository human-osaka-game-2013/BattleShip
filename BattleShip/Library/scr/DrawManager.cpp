#include "DrawManager.h"

//	�R���X�g���N�^
CDrawManagher::CDrawManagher( IDirect3DDevice9* const _pD3Device):
	m_pD3Device(_pD3Device)
{
	if( !AllLoadTexture())	{

	}
}

CDrawManagher::~CDrawManagher()
{
	ReleaseAllTexture();
}