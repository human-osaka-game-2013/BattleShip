#include "DrawManager.h"

void CDrawManager::VertexDraw ( int _textuerNumber, CUSTOMVERTEX (&_vertex)[4] )
{

	m_pD3Device -> SetTexture ( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		_vertex,
		sizeof ( CUSTOMVERTEX ) );
}

void CDrawManager::VertexDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
			float _fTu, float _fTv, float _fTu2, float _fTv2)
{
	CUSTOMVERTEX customVertex[4] ={
		{ _fXpos			, _fYpos			, 0.5f, 1.0f, 0xffffffff, _fTu, _fTv },
		{ _fXpos+_fWidth	, _fYpos			, 0.5f, 1.0f, 0xffffffff, _fTu2, _fTv },
		{ _fXpos+_fWidth	, _fYpos+_fHeight , 0.5f, 1.0f, 0xffffffff, _fTu2, _fTv2 },
		{ _fXpos			, _fYpos+_fHeight , 0.5f, 1.0f, 0xffffffff, _fTu, _fTv2 }
	};

	m_pD3Device -> SetTexture ( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );
}

void CDrawManager::VertexDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
				float _fTu, float _fTv, float _fTu2, float _fTv2, int _iA, int _iR, int _iG, int _iB )
{
	CUSTOMVERTEX customVertex[4] ={
	 { _fXpos		, _fYpos			, 0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu, _fTv },
	 { _fXpos+_fWidth	, _fYpos			, 0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu2, _fTv },
	 { _fXpos+_fWidth	, _fYpos+_fHeight , 0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu2, _fTv2 },
	 { _fXpos		, _fYpos+_fHeight , 0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu, _fTv2 }
	};

	m_pD3Device -> SetTexture ( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );
}

void CDrawManager::CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
						float _fTu1, float _fTv1, float _fTu2, float _fTv2 )
{
	CUSTOMVERTEX customVertex[4] = {
		{ _fXpos -_fWidth/2, _fYpos -_fHeight/2, 0.5f, 1.0f, 0xffffffff, _fTu1, _fTv1 },
		{ _fXpos + _fWidth/2, _fYpos -_fHeight/2, 0.5f, 1.0f, 0xffffffff, _fTu2, _fTv1 },
		{ _fXpos + _fWidth/2, _fYpos +_fHeight/2, 0.5f, 1.0f, 0xffffffff, _fTu2, _fTv2 },
		{ _fXpos -_fWidth/2, _fYpos +_fHeight/2, 0.5f, 1.0f, 0xffffffff, _fTu1, _fTv2 },
	};

	
	m_pD3Device -> SetTexture ( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}

void CDrawManager::CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fAngle, float _fWidth, float _fHeight,
						float _fTu1, float _fTv1, float _fTu2, float _fTv2 )
{
	float fRad = _fAngle * D3DX_PI / 180.0f;

	CUSTOMVERTEX customVertex[4] = {
		{ _fXpos + ( -_fWidth/2 ) * cosf ( fRad ) - ( -_fHeight/2 ) * sinf ( fRad ),
		  _fYpos + ( -_fWidth/2 ) * sinf ( fRad ) + ( -_fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, _fTu1, _fTv1 },
		
		{ _fXpos + _fWidth/2 * cosf ( fRad ) - ( -_fHeight/2 ) * sinf ( fRad ),
		  _fYpos + _fWidth/2 * sinf ( fRad ) + ( -_fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, _fTu2, _fTv1 },
		
		{ _fXpos + _fWidth/2 * cosf ( fRad ) - _fHeight/2 * sinf ( fRad ),
		  _fYpos + _fWidth/2 * sinf ( fRad ) + _fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, _fTu2, _fTv2 },
		
		{ _fXpos + ( -_fWidth/2 ) * cosf ( fRad ) - _fHeight/2 * sinf ( fRad ),
		  _fYpos + ( -_fWidth/2 ) * sinf ( fRad ) + _fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, _fTu1, _fTv2 },
	};

	m_pD3Device -> SetTexture ( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}

void CDrawManager::CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fAngle, float _fWidth, float _fHeight,
						float _fTu1, float _fTv1, float _fTu2, float _fTv2, int _iA, int _iR, int _iG, int _iB )
{
	float fRad = _fAngle * D3DX_PI / 180.0f;

	CUSTOMVERTEX customVertex[4] = {
		{ _fXpos + ( -_fWidth/2 ) * cosf ( fRad ) - ( -_fHeight/2 ) * sinf ( fRad ),
		  _fYpos + ( -_fWidth/2 ) * sinf ( fRad ) + ( -_fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu1, _fTv1 },
		
		{ _fXpos + _fWidth/2 * cosf ( fRad ) - ( -_fHeight/2 ) * sinf ( fRad ),
		  _fYpos + _fWidth/2 * sinf ( fRad ) + ( -_fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu2, _fTv1 },
		
		{ _fXpos + _fWidth/2 * cosf ( fRad ) - _fHeight/2 * sinf ( fRad ),
		  _fYpos + _fWidth/2 * sinf ( fRad ) + _fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu2, _fTv2 },
		
		{ _fXpos + ( -_fWidth/2 ) * cosf ( fRad ) - _fHeight/2 * sinf ( fRad ),
		  _fYpos + ( -_fWidth/2 ) * sinf ( fRad ) + _fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( _iA, _iR, _iG, _iB ), _fTu1, _fTv2 },
	};

	m_pD3Device -> SetTexture ( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}

void CDrawManager::AnimationDraw( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight, 
						unsigned int _tuSize, unsigned int _tvSize )
{
	CUSTOMVERTEX customVertex[4];

	_tuSize = _tuSize%m_TextureInfo[_textuerNumber].width;
	_tvSize = _tvSize%m_TextureInfo[_textuerNumber].height;

	float tu1 = static_cast<float>( _tuSize / m_TextureInfo[_textuerNumber].width );
	float tv1 = static_cast<float>( _tvSize / m_TextureInfo[_textuerNumber].height);
	float tu2 = static_cast<float>( (_tuSize + _fWidth) / m_TextureInfo[_textuerNumber].width  );
	float tv2 = static_cast<float>( (_tvSize + _fHeight) / m_TextureInfo[_textuerNumber].height);

	for( int i = 0; i < 4; i++ )
	{
		customVertex[i].z = 0.5f;
		customVertex[i].rhw = 1.0f;
		customVertex[i].color = 0xffffffff;
	}

	customVertex[0].x	= _fXpos;
	customVertex[0].y	= _fYpos;
	customVertex[1].x	= _fXpos + _fWidth;
	customVertex[1].y	= _fYpos;
	customVertex[2].x	= _fXpos + _fWidth;
	customVertex[2].y	= _fYpos +_fHeight;
	customVertex[3].x	= _fXpos;
	customVertex[3].y	= _fYpos +_fHeight;
	
	customVertex[0].tu	= tu1;
	customVertex[0].tv	= tv1;
	customVertex[1].tu	= tu2;
	customVertex[1].tv	= tv1;
	customVertex[2].tu	= tu2;
	customVertex[2].tv	= tv2;
	customVertex[3].tu	= tu1;
	customVertex[3].tv	= tv2;
	
	m_pD3Device -> SetTexture( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );
}

void CDrawManager::AnimationDraw( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
									bool _flipHorizontal, bool _flipVertical, int _wDiv, int _hDiv, unsigned long _color )
{
	CUSTOMVERTEX customVertex[4];

	float tu1 = m_TextureInfo[_textuerNumber].divTuSize*(_wDiv%m_TextureInfo[_textuerNumber].wDiv);
	float tv1 = m_TextureInfo[_textuerNumber].divTvSize*(_hDiv%m_TextureInfo[_textuerNumber].hDiv);
	float tu2 = tu1+m_TextureInfo[_textuerNumber].divTuSize;
	float tv2 = tv1+m_TextureInfo[_textuerNumber].divTvSize;


	for( int i = 0; i < 4; i++ )
	{
		customVertex[i].z = 0.5f;
		customVertex[i].rhw = 1.0f;
		customVertex[i].color = _color;
	}

	customVertex[0].x	= _fXpos;
	customVertex[0].y	= _fYpos;
	customVertex[1].x	= _fXpos + _fWidth;
	customVertex[1].y	= _fYpos;
	customVertex[2].x	= _fXpos + _fWidth;
	customVertex[2].y	= _fYpos +_fHeight;
	customVertex[3].x	= _fXpos;
	customVertex[3].y	= _fYpos +_fHeight;

	if( !_flipHorizontal )
	{
		
		customVertex[0].tu	= tu1;
		customVertex[0].tv	= tv1;
		
		customVertex[1].tu	= tu2;
		customVertex[1].tv	= tv1;

		customVertex[2].tu	= tu2;
		customVertex[2].tv	= tv2;

		customVertex[3].tu	= tu1;
		customVertex[3].tv	= tv2;
		
	}
	else
	{
		customVertex[0].tu	= tu2;
		customVertex[0].tv	= tv1;
		
		customVertex[1].tu	= tu1;
		customVertex[1].tv	= tv1;
		
		customVertex[2].tu	= tu1;
		customVertex[2].tv	= tv2;
		
		customVertex[3].tu	= tu2;
		customVertex[3].tv	= tv2;
	}
	if( _flipVertical )
	{
		float tempTU[4] = { customVertex[0].tu, customVertex[1].tu,
							customVertex[2].tu, customVertex[3].tu };
		float tempTV[4] = { customVertex[0].tv, customVertex[1].tv,
							customVertex[2].tv, customVertex[3].tv };

		customVertex[0].tu	= tempTU[3];
		customVertex[0].tv	= tempTV[3];
		
		customVertex[1].tu	= tempTU[2];
		customVertex[1].tv	= tempTV[2];
		
		customVertex[2].tu	= tempTU[1];
		customVertex[2].tv	= tempTV[1];
		
		customVertex[3].tu	= tempTU[0];
		customVertex[3].tv	= tempTV[0];
	}


	m_pD3Device -> SetTexture( 0, m_TextureInfo[_textuerNumber].pTexture );
	m_pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );
}

void CDrawManager::VertexTransform(  int _textuerNumber, CUSTOMVERTEX (&_vertex)[4], float _fPosX, float _fPosY, 
		float _fScaleX, float _fScaleY, float _fRotationZ)
{
	float fRad = _fRotationZ * D3DX_PI / 180.f;

	CUSTOMVERTEX tempVertex[4];

	//	ïœä∑åãâ Çäiî[Ç∑ÇÈãÈå`ÇÃèâä˙âª
	tempVertex[0].tu = _vertex[0].tu;
	tempVertex[0].tv = _vertex[0].tv;
	tempVertex[1].tu = _vertex[1].tu;
	tempVertex[1].tv = _vertex[1].tv;
	tempVertex[2].tu = _vertex[2].tu;
	tempVertex[2].tv = _vertex[2].tv;
	tempVertex[3].tu = _vertex[3].tu;
	tempVertex[3].tv = _vertex[3].tv;
		
	for (int i = 0; i < 4; i++) {
		tempVertex[i].x = 0.f;
		tempVertex[i].y = 0.f;
		tempVertex[i].z = 0.f;
		tempVertex[i].rhw = 1.0f;
		tempVertex[i].color = _vertex[i].color;
	}

	for( int iCount = 0; iCount < 4; iCount++ ){
		D3DXMATRIXA16	matWorld, matPosition, matScale, matRotation;
		D3DXMatrixIdentity( &matWorld );
		D3DXMatrixRotationZ( &matRotation, fRad );
		D3DXMatrixScaling( &matScale, _fScaleX, _fScaleY, 1.f);
		D3DXMatrixTranslation( &matPosition, _vertex[iCount].x, _vertex[iCount].y, _vertex[iCount].z);

		D3DXMatrixMultiply(&matWorld,&matWorld,&matScale);		///<ägèkî{ó¶ÇÇ©ÇØÇÈ
		D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);	///<äeí∏ì_ÇÃÉçÅ[ÉJÉãç¿ïWÇÇ©ÇØÇÈ
		D3DXMatrixMultiply(&matWorld,&matWorld,&matRotation);	///<âÒì]ìxÇÇ©ÇØÇÈ
		
		//ïœä∑å„ÇÃÉçÅ[ÉJÉãç¿ïWÇ…äÓèÄì_ï™Çë´Ç∑
		tempVertex[iCount].x = matWorld._41 + _fPosX;
		tempVertex[iCount].y = matWorld._42 + _fPosY;
		tempVertex[iCount].z = matWorld._43;
	}

	VertexDraw( _textuerNumber, tempVertex);	///<ï`âÊ
}
