/**
*@file	DrawManage.h
*@author	亀田
*/

#ifndef _DRAW_MANAGE_H_
#define _DRAW_MANAGE_H_

#include "lib_head.h"

// テクスチャの番号とテクスチャ全体の縦横の大きさ
struct TEXTUREINFO
{
	// テクスチャの格納ポインタ
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
};

// 画像の頂点座標などの構造体
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};


// 使用するテクスチャ
// 使いたいテクスチャがあれば列挙子内に追加していく
enum TEXTURES
{

	_TEX_BACKGROUND_,
	_TEX_AIRCARRIER_,
	_TEX_BATTLESHIP_,
	_TEX_CRUISER_,
	_TEX_DESTROYER_,
	_TEX_SUBMARINE_,
	_TEX_STAGEMAP_,
	_TEX_BLOCK_,

	_TEXTURE_MAX_
};

/**
*@brief	2D描画クラス
*@details	シーン管理クラスに実体を持たせ、各シーンクラスにポインタを渡す。	
*@todo	アドレスをconstにするのは初めてなので、修正する可能性もあり。
*/
class CDrawManager
{
private:
	TEXTUREINFO m_TextureInfo [_TEXTURE_MAX_];	///<テクスチャ情報格納配列
	IDirect3DDevice9* const m_pD3Device;		///<D3Dデバイスポインタ


public:
	/**
	*@brief	コンストラクタ
	*/
	CDrawManager( IDirect3DDevice9* const _pD3Device);
	/**
	*@brief	デストラクタ
	*/
	~CDrawManager();

public:
	/**
	*@brief 描画前処理
	*param[in] _b3dView：3D描画などをする場合など、@n
						描画設定の再設定をする場合にtrueを渡す。
	*/
	void BeginDraw ( bool _b3dView = false );

	// テクスチャの読み込み
	// 第1引数：("画像の名前.拡張子"), 第2引数：テクスチャの番号, 透過色RGB 
	bool LoadTexture ( LPCSTR _lpFileName, int _textuerNumber, int _iColorRed, int _iColorGreen, int _iColorBlue );

	// テクスチャの解放
	// 第1引数：テクスチャの番号
	void ReleaseTexture ( int _textuerNumber );
	
	void ReleaseAllTexture ();

public:

	//	(左上基準で)描画
	//	引数>1：テクスチャの番号 2,3：描画の基準となる左上の点xy, 4,5：頂点の縦横幅 
	//	6,7：左上uv座標 8,9：右下uv座標 
	void VertexDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
				float fTu, float fTv, float fTu2, float fTv2);
	
	//	色調を変えて(左上基準で)描画
	//	引数>1：テクスチャの番号 2,3：描画の基準となる左上の点xy, 4,5：頂点の縦横幅 
	//	6,7：左上uv座標 8,9：右下uv座標 
	//	引数＞11～14：：ARGB値
	void CustomCorolDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
					float fTu, float fTv, float fTu2, float fTv2, int iA, int iR, int iG, int iB );
	
	//	中心点から描画
	//	引数＞1：テクスチャの番号 2,3：基準となる中心点 4,5：画像の縦横幅
	//	引数＞6,7：画像の左上のUV座標 8,9:画像の右下のUV座標
	void CenterDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
							float fTu1, float fTv1, float fTu2, float fTv2 );
	
	//	中心点から描画 (回転)
	//	引数＞1：テクスチャの番号 2,3：基準となる中心点 4：傾けたい角度(傾けないなら0でOK) 5,6：画像の縦横幅
	//	引数＞7,8：画像の左上のUV座標 9,10:画像の右下のUV座標
	void SpinerDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
							float fTu1, float fTv1, float fTu2, float fTv2 );
	
	//	中心点から描画 (色調変化)
	//	引数＞1：テクスチャの番号 2,3：基準となる中心点 4：傾けたい角度(傾けないなら0でOK) 5,6：頂点の縦横幅
	//	引数＞7,8：左上のUV座標 9,10:右下のUV座標 11～14：ARGB値
	void ColorKeyDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
							float fTu1, float fTv1, float fTu2, float fTv2, int iA, int iR, int iG, int iB );
	
	//	中心点から描画 (伸縮)
	//	引数＞1：テクスチャの番号 2,3：伸縮させる基準点X,Y 4：角度 5,6：画像の縦横幅
	//	引数＞7,8：左上のUV座標 9,10:右下のUV座標 11～14：ARGB値
	void ElasticityDraw ( int TextuerNumber, float fXpos, float fYpos, float& fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int& iA, int& iR, int& iG, int& iB );


public:
	//	使用する全ての画像を読み込み
	virtual bool AllLoadTexture ();
};

#endif