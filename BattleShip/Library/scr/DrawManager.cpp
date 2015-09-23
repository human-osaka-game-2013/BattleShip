#include "DrawManager.h"

//	コンストラクタ
CDrawManager::CDrawManager( IDirect3DDevice9* const _pD3Device):
	m_pD3Device(_pD3Device)
{
	if( !AllLoadTexture())	{

	}
}

CDrawManager::~CDrawManager()
{
	ReleaseAllTexture();
}