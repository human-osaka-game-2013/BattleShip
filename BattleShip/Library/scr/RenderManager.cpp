#include "RenderManager.h"

/*
	背景板ポリの数値
*/
const float fWidth = 10.f, fHeight = 10.f;
const float fTu1 = 0.f, fTv1 = 0.f, fTu2 = 1.f, fTv2 = 1.f;

/*
	コンストラクタ
*/
CRenderManager::CRenderManager( IDirect3DDevice9* const _pD3Device, 
					IDirectInputDevice8* const _pMouseDevice ):
	m_pD3Device( _pD3Device ), m_pMouseDevice( _pMouseDevice ),
	INIT_EYE_POS( 0.f, 0.f, -100.f ), INIT_LOOK_POS( 0.f, 0.f, 0.f ), 
	LEFT_ROT(0.f*D3DX_PI/180.f, 90.f*D3DX_PI/180.f, 0.f), RIGHT_ROT(0.f*D3DX_PI/180.f, -90.f*D3DX_PI/180.f, 0.f ),
	CENTER_ROT(0.f*D3DX_PI/180.f, 0.f*D3DX_PI/180.f, 0.f), vecCursorPos( 0.f,0.f, 0.f )
{
	if( !AllLoadXFile() ){

	}
	
}

/*
	デストラクタ
*/
CRenderManager::~CRenderManager()
{
	AllReleaseMesh();
}
