#include "DrawManager.h"

//	コンストラクタ
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