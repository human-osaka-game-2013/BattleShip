/**
*@file	RenderManager.h
*@author	亀田
*/

#ifndef _RENDER_MANAGE_H_
#define _RENDER_MANAGE_H_

#include "device.h"
#include "AllocateHierarchy.h"
#include "gameObject.h"

#include "Window.h"

//	メッシュデータ
struct MESH_INFO
{
	LPD3DXMESH			pMesh;			//	メッシュデータの格納
	D3DMATERIAL9*		pMeshMaterials;	//	マテリアルのデータ
	LPDIRECT3DTEXTURE9*	pMeshTextures;	//	テクスチャのデータ
	DWORD				dwNumMaterials;	//	
};

//	カメラ情報
struct CAMERA_INFO
{
	D3DXVECTOR3 eyePos;		// 視点座標xyz
	D3DXVECTOR3 lookPos;	// 注視点座標xyz
	float		radian;		// 視点回転補正度
};

/**
*@brief	3D描画クラス
*@details	シーン管理クラスに実体を持たせ、各シーンクラスにポインタを渡す。	
*@todo	アドレスをconstにするのは初めてなので、修正する可能性もあり。
*/
class CRenderManager
{
public:
	//	使用するメッシュファイルをIDとして列挙
	enum MESH_ID
	{
		MESH_BG1,

		MESH_BOX_1,

		MESH_BULLET,

		MESH_MAX
	};

	//	使用するアニメーション付きメッシュファイルを
	//	IDとして列挙
	enum ANIM_MESH_ID
	{
		AN_WAIT = CGameObject::STATE_WAIT,

		AN_RUN = CGameObject::STATE_WALK,

		AN_JUMP = CGameObject::STATE_JUMP,

		AN_DOWN = CGameObject::STATE_DOWN,

		AN_MESH_MAX
	};

public:
	const D3DXVECTOR3 LEFT_ROT;
	const D3DXVECTOR3 RIGHT_ROT;
	const D3DXVECTOR3 CENTER_ROT;
	const D3DXVECTOR3 INIT_EYE_POS;
	const D3DXVECTOR3 INIT_LOOK_POS;
	D3DXVECTOR3	vecCursorPos;

	//	アニメーション付きメッシュデータ保存変数
	CAllocateHierarchy AllocateHierarchy[ AN_MESH_MAX ];

private:
	MESH_INFO MeshInfo[ MESH_MAX ];	//	メッシュデータ保存用メンバ変数

	CAMERA_INFO CameraInfo;		//	カメラ情報保存用メンバ変数

	IDirect3DDevice9* const	m_pD3Device;	///<D3Dデバイス
	IDirectInputDevice8* const m_pMouseDevice;	///<マウスデバイス(マウス座標の変換に必要)

public:
	/**
	*@brief	コンストラクタ
	*@param[in]	_pD3Device	
	*/
	CRenderManager( IDirect3DDevice9* const _pD3Device, 
					IDirectInputDevice8* const _pMouseDevice );

	/**
	*@brief	デストラクタ
	*/
	~CRenderManager();

	/**
	*@brief	視点座標の取得
	*@return CameraInfo.eyePos
	*/
	D3DXVECTOR3 GetEyePos() { return CameraInfo.eyePos; }
	
	/**
	*@brief	注視点座標の取得
	*@return CameraInfo.lookPos
	*/
	D3DXVECTOR3 GetLookPos(){ return CameraInfo.lookPos; }
	
	/**
	*@brief	視点回転補正度の取得
	*@return CameraInfo.radian
	*/
	float GetRad()	{ return CameraInfo.radian; }

public:
	

	/*
		ビルボード用の頂点描画
	*/
	void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition );
	
	//	3D描画処理
	void Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	//	3Dアニメーション付き描画処理
	void AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	

	// スクリーン座標をワールド座標に変換
	D3DXVECTOR3* CalcScreenToWorld
	(
	   D3DXVECTOR3* pout,	
	   int Sx,				//	スクリーン座標内ｘ
	   int Sy,				//	スクリーン座標内ｙ
	   float fZ,			//	射影空間でのZ値（0～1）
	   int Screen_w,		//	スクリーンの横幅
	   int Screen_h,		//	スクリーンの縦幅
	   D3DXMATRIXA16* View,	//	ビュー行列
	   D3DXMATRIXA16* Prj		//	射影変換行列
	);

	/**
	*@brief	スクリーン座標内のマウス座標をワールド座標に変換
	*@param[in]	_cursorMovePosX	マウス移動量X。CMouseクラスから取得
	*@param[in]	_cursorMovePosY	マウス移動量Y。CMouseクラスから取得
	*/
	void MousePosTransform( long _cursorMovePosX, long _cursorMovePosY );

public:
	/**
	*@brief	3D描画前処理
	*/
	void BeginRender();

	//	xファイル読み込み
	//	(in)メッシュファイルのID，ファイルアドレス (out)読み込み成功→true	失敗→false
	bool LoadXFile( MESH_ID _id, LPCSTR _xFileName );

	//	カメラ情報初期化
	void CameraInit();

	//	メッシュデータの解放
	void ReleaseMesh( int _id );

	//	全メッシュデータを解放
	void AllReleaseMesh();

public:
	//	
	virtual bool AllLoadXFile();
};

#endif