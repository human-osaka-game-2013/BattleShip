#include "RenderManager.h"

// 3D描画前処理
void CRenderManager::BeginRender( )
{
	
	if ( !m_pD3Device )
	{

	}
	m_pD3Device->SetRenderState( D3DRS_ZENABLE, TRUE );			// Zバッファー処理を有効に
	//m_pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// カリングしない
	m_pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	// カリングする
	m_pD3Device->SetRenderState( D3DRS_LIGHTING, TRUE );			// ライトを有効に
	m_pD3Device->SetRenderState( D3DRS_AMBIENT, 0x00000000 );		// アンビエントライト(環境光)を設定
	m_pD3Device->SetRenderState( D3DRS_SPECULARENABLE, TRUE );	// スペキュラ(鏡面反射)を有効に
	m_pD3Device->LightEnable(0, TRUE);

	// 画面の消去
	m_pD3Device -> Clear (0, NULL,
						D3DCLEAR_TARGET ,
						D3DCOLOR_XRGB ( 0x20, 0x50, 0x50 ),
						1.0, 0 );

	// 描画の開始
	m_pD3Device -> BeginScene();
}

/*
	メッシュの読込＆裏描画バッファ
*/
bool CRenderManager::LoadXFile( MESH_ID _id, LPCSTR _xFileName )
{
	//xファイルからメッシュをロードする
	LPD3DXBUFFER	pD3DXMtrlBuffer	= NULL;

	if (FAILED(D3DXLoadMeshFromX(
		_xFileName,
		D3DXMESH_SYSTEMMEM,
		m_pD3Device,
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&MeshInfo[ _id ].dwNumMaterials,
		&MeshInfo[ _id ].pMesh
		) ) )
	{
		MessageBoxA(NULL,"xファイルの読み込みに失敗しました",_xFileName,MB_OK);
		return false;
	}


	D3DXMATERIAL*	d3dxMaterials	= (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	MeshInfo[ _id ].pMeshMaterials		= new D3DMATERIAL9[MeshInfo[ _id ].dwNumMaterials];
	MeshInfo[ _id ].pMeshTextures		= new LPDIRECT3DTEXTURE9[MeshInfo[ _id ].dwNumMaterials];

	for (DWORD i=0;	i<MeshInfo[ _id ].dwNumMaterials;	i++)
	{
		MeshInfo[ _id ].pMeshMaterials[i]			= d3dxMaterials[i].MatD3D;
		MeshInfo[ _id ].pMeshMaterials[i].Ambient	= MeshInfo[ _id ].pMeshMaterials[i].Diffuse;
		MeshInfo[ _id ].pMeshTextures[i]			= NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) >0)
		{
			if (FAILED (D3DXCreateTextureFromFileEx (m_pD3Device,
													d3dxMaterials[i].pTextureFilename,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT,
													0,
													D3DFMT_UNKNOWN,
													D3DPOOL_MANAGED,
													D3DX_FILTER_NONE,
													D3DX_FILTER_NONE,
													D3DCOLOR_ARGB ( 0, 0, 255, 0),
													NULL, NULL,
													&MeshInfo[ _id ].pMeshTextures[i]) ) )
			{
				MessageBox(NULL,TEXT("テクスチャの読み込みに失敗しました"),NULL,MB_OK);
			}
		}
	}

	
	pD3DXMtrlBuffer->Release();

	return true;
}

/*
	カメラ情報初期化
*/
void CRenderManager::CameraInit()
{
	//視点の初期化
	CameraInfo.eyePos.x = INIT_EYE_POS.x;
	CameraInfo.eyePos.y = INIT_EYE_POS.y;
	CameraInfo.eyePos.z = INIT_EYE_POS.z;

	//注視点の初期化
	CameraInfo.lookPos.x = INIT_LOOK_POS.x;
	CameraInfo.lookPos.y = INIT_LOOK_POS.y;
	CameraInfo.lookPos.z = INIT_LOOK_POS.z;

	//回転に使用
	CameraInfo.radian = atan2f( INIT_LOOK_POS.x, INIT_LOOK_POS.z);
}


/*
	メッシュデータの解放
*/
void CRenderManager::ReleaseMesh( int _id )
{
	//メッシュ解放
	SAFE_RELEASE( MeshInfo[ _id ].pMesh );
	
	//テクスチャ解放
	for ( DWORD i = 0; i < MeshInfo[ _id ].dwNumMaterials; i++ )
	{
		SAFE_RELEASE( MeshInfo[ _id ].pMeshTextures[i] );
	}
	 
	//配列解放
	NULL_ARRAY_DELETE( MeshInfo[ _id ].pMeshTextures);
	NULL_ARRAY_DELETE( MeshInfo[ _id ].pMeshMaterials);

}

/*
	全メッシュデータを解放
*/
void CRenderManager::AllReleaseMesh()
{
	for ( int iCount = 0; iCount < MESH_MAX; iCount++ )
	{
		ReleaseMesh( iCount );
	}
	for ( int iCount = 0; iCount < AN_MESH_MAX; iCount++ )
	{
		LPD3DXFRAME pFrame = NULL;
		pFrame = AllocateHierarchy[iCount].GetFrame();
		AllocateHierarchy[iCount].DestroyFrame( pFrame );
		AllocateHierarchy[iCount].GetAnimCtrl()->Release();
	}
}
