#include "DrawManager.h"

// 描画前処理
void CDrawManager::BeginDraw( bool _b3dView )
{
	static bool _SetStateFlag = false;
	if ( !m_pD3Device )
	{

	}
	if( _b3dView || !_SetStateFlag )
	{
		// ステージステートの設定
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_COLOROP,	D3DTOP_MODULATE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE	);
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
		m_pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE	);
		
		// 描画方法の設定
		m_pD3Device -> SetRenderState ( D3DRS_ALPHABLENDENABLE,	true );
		
		m_pD3Device ->  SetRenderState ( D3DRS_SRCBLEND,	D3DBLEND_SRCALPHA	);
		m_pD3Device ->  SetRenderState ( D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA);
		//m_pD3Device ->  SetRenderState ( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1		);

		m_pD3Device -> SetRenderState ( D3DRS_ZENABLE, false );
		_SetStateFlag = true;
	}

	// 画面の消去
	if(	m_pD3Device -> Clear (0, NULL,
							D3DCLEAR_TARGET ,
							D3DCOLOR_XRGB ( 0x00, 0x00, 0x00 ),
							1.0, 0 ) != D3D_OK)
	{
		MessageBoxA(0, "Clear is Fail", NULL,MB_OK );
	}

	// 描画の開始
	m_pD3Device -> BeginScene();

	// 画面の描画
	m_pD3Device -> SetFVF ( D3DFVF_CUSTOMVERTEX );

}

// テクスチャの読み込み
// 第1引数：("画像の名前.拡張子"), 第2引数：テクスチャの番号, 透過色RGB 
bool CDrawManager::LoadTexture ( LPCSTR _lpFileName, int _textuerNumber, int _iColorRed, int _iColorGreen, int _iColorBlue )
{
	// テクスチャを既に読み込んでいる場合はここで解放する
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
						MessageBoxA(0,"テクスチャが読み込めませんでした(＞＜;)",NULL,MB_OK);
						return false;
	}

	// テクスチャ情報取得
	D3DSURFACE_DESC desc;

	m_TextureInfo [_textuerNumber].pTexture -> GetLevelDesc ( 0, &desc );
	m_TextureInfo [_textuerNumber].width = desc.Width;
	m_TextureInfo [_textuerNumber].height = desc.Height;

	

	return true;
}


// テクスチャの解放
// 第1引数：テクスチャの番号
void CDrawManager::ReleaseTexture ( int _textuerNumber )
{
	SAFE_RELEASE ( m_TextureInfo[_textuerNumber].pTexture );
}

// 使用している全てのテクスチャの解放
void CDrawManager::ReleaseAllTexture ()
{
	for ( int i = 0; i < _TEXTURE_MAX_; i++ )
	{
		ReleaseTexture (i);
	}
}