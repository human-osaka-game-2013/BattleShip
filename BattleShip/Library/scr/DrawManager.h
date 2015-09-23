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
	_TEX_BLOCKFRAME_,
	_TEX_TABFRAME_,
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
	/**
	*@brief	矩形描画
	*@details	外部から矩形情報を貰う場合の描画
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_vertex 矩形情報
	*/
	void VertexDraw( int _textuerNumber, CUSTOMVERTEX (&_vertex)[4] );

	/**
	*@brief	矩形描画
	*@details	左上の頂点基準の場合の描画
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_fXpos		矩形の左上頂点座標X
	*@param[in]	_fYpos		矩形の左上頂点座標Y
	*@param[in]	_fWidth		矩形の横幅
	*@param[in]	_fHeight	矩形の縦幅
	*@param[in]	_fTu		矩形の左上頂点テクスチャ座標U
	*@param[in]	_fTv		矩形の左上頂点テクスチャ座標V
	*@param[in]	_fTu2		矩形の右下頂点テクスチャ座標U
	*@param[in]	_fTv2		矩形の右下頂点テクスチャ座標V
	*/
	void VertexDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
				float _fTu, float _fTv, float _fTu2, float _fTv2);
	
	/**
	*@brief	矩形描画
	*@details	左上の頂点基準でカラー値の変更も必要な場合の描画
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_fXpos		矩形の左上頂点座標X
	*@param[in]	_fYpos		矩形の左上頂点座標Y
	*@param[in]	_fWidth		矩形の横幅
	*@param[in]	_fHeight	矩形の縦幅
	*@param[in]	_fTu		矩形の左上頂点テクスチャ座標U
	*@param[in]	_fTv		矩形の左上頂点テクスチャ座標V
	*@param[in]	_fTu2		矩形の右下頂点テクスチャ座標U
	*@param[in]	_fTv2		矩形の右下頂点テクスチャ座標V
	*@param[in]	_iA			矩形のカラー値（透明度）
	*@param[in]	_iR			矩形のカラー値（赤）
	*@param[in]	_iG			矩形のカラー値（緑）
	*@param[in]	_iB			矩形のカラー値（青）
	*/
	void VertexDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
					float _fTu, float _fTv, float _fTu2, float _fTv2, int _iA, int _iR, int _iG, int _iB );
	
	/**
	*@brief	中心基準の矩形描画
	*@details	矩形の中心基準の場合の描画
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_fXpos		矩形の中心座標X
	*@param[in]	_fYpos		矩形の中心座標Y
	*@param[in]	_fWidth		矩形の横幅
	*@param[in]	_fHeight	矩形の縦幅
	*@param[in]	_fTu1		矩形の左上頂点テクスチャ座標U
	*@param[in]	_fTv1		矩形の左上頂点テクスチャ座標V
	*@param[in]	_fTu2		矩形の右下頂点テクスチャ座標U
	*@param[in]	_fTv2		矩形の右下頂点テクスチャ座標V
	*/
	void CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
							float _fTu1, float _fTv1, float _fTu2, float _fTv2 );
	
	/**
	*@brief	中心基準の矩形描画
	*@details	矩形の中心基準で回転させる必要がある場合の描画
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_fXpos		矩形の中心座標X
	*@param[in]	_fYpos		矩形の中心座標Y
	*@param[in]	_fAngle		矩形の回転角度
	*@param[in]	_fWidth		矩形の横幅
	*@param[in]	_fHeight	矩形の縦幅
	*@param[in]	_fTu1		矩形の左上頂点テクスチャ座標U
	*@param[in]	_fTv1		矩形の左上頂点テクスチャ座標V
	*@param[in]	_fTu2		矩形の右下頂点テクスチャ座標U
	*@param[in]	_fTv2		矩形の右下頂点テクスチャ座標V
	*/
	void CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fAngle, float _fWidth, float _fHeight,
							float _fTu1, float _fTv1, float _fTu2, float _fTv2 );
	
	/**
	*@brief	中心基準の矩形描画
	*@details	矩形の中心基準でカラー値を変更する場合の描画
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_fXpos		矩形の中心座標X
	*@param[in]	_fYpos		矩形の中心座標Y
	*@param[in]	_fAngle		矩形の回転角度
	*@param[in]	_fWidth		矩形の横幅
	*@param[in]	_fHeight	矩形の縦幅
	*@param[in]	_fTu1		矩形の左上頂点テクスチャ座標U
	*@param[in]	_fTv1		矩形の左上頂点テクスチャ座標V
	*@param[in]	_fTu2		矩形の右下頂点テクスチャ座標U
	*@param[in]	_fTv2		矩形の右下頂点テクスチャ座標V
	*@param[in]	_iA			矩形のカラー値（透明度）
	*@param[in]	_iR			矩形のカラー値（赤）
	*@param[in]	_iG			矩形のカラー値（緑）
	*@param[in]	_iB			矩形のカラー値（青）
	*/
	void CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fAngle, float _fWidth, float _fHeight,
							float _fTu1, float _fTv1, float _fTu2, float _fTv2, int _iA, int _iR, int _iG, int _iB );

	/**
	*@brief	矩形の座標変換
	*@details	ローカル座標情報を持った矩形情報を基準で変換を行う（現在はついでに描画もする）
	*@parap[in] _textuerNumber テクスチャの番号
	*@param[in]	_vertex 矩形情報
	*@param[in]	_fXpos	矩形の基準座標X
	*@param[in]	_fYpos	矩形の基準座標Y
	*@param[in]	_fScaleX	矩形の拡縮X
	*@param[in]	_fScaleY	矩形の拡縮Y
	*@param[in]	_fRotationY	矩形の回転角度
	*/
	void VertexTransform(  int _textuerNumber, CUSTOMVERTEX (&_vertex)[4], float _fPosX, float _fPosY, 
		float _fScaleX, float _fScaleY, float _fRotationZ);

public:
	//	使用する全ての画像を読み込み
	virtual bool AllLoadTexture ();
};

#endif