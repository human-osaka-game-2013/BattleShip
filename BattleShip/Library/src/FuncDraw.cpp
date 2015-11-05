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

void CDrawManager::VertexTransform(  int _textuerNumber, CUSTOMVERTEX (&_vertex)[4], float _fPosX, float _fPosY, 
		float _fScaleX, float _fScaleY, float _fRotationZ)
{
	float fRad = _fRotationZ * D3DX_PI / 180.f;

	CUSTOMVERTEX tempVertex[4];

	//	変換結果を格納する矩形の初期化
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
		tempVertex[i].color = 0xFFFFFFFF;
	}

	for( int iCount = 0; iCount < 4; iCount++ ){
		D3DXMATRIXA16	matWorld, matPosition, matScale, matRotation;
		D3DXMatrixIdentity( &matWorld );
		D3DXMatrixRotationZ( &matRotation, fRad );
		D3DXMatrixScaling( &matScale, _fScaleX, _fScaleY, 1.f);
		D3DXMatrixTranslation( &matPosition, _vertex[iCount].x, _vertex[iCount].y, _vertex[iCount].z);

		D3DXMatrixMultiply(&matWorld,&matWorld,&matScale);		///<拡縮倍率をかける
		D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);	///<各頂点のローカル座標をかける
		D3DXMatrixMultiply(&matWorld,&matWorld,&matRotation);	///<回転度をかける
		
		//変換後のローカル座標に基準点分を足す
		tempVertex[iCount].x = matWorld._41 + _fPosX;
		tempVertex[iCount].y = matWorld._42 + _fPosY;
		tempVertex[iCount].z = matWorld._43;
	}

	VertexDraw( _textuerNumber, tempVertex);	///<描画
}