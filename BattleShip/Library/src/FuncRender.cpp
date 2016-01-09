/**
*@file	FuncRender.cpp
*@author	亀田
*@brief	3D描画系関数まとめ
*/

#include "RenderManager.h"


/*
	3D描画処理
*/
void CRenderManager::Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall )
{

	//ワールドトランスフォーム(絶対座標変換)
	//matWorld->y軸回転
	D3DXMATRIXA16	matWorld, matPosition, matScall, matRoate;						//[最終的なワールドトランスフォーム][平行移動行列を格納する行列]
	D3DXMatrixIdentity(&matWorld);												//単位行列の作成関数
	D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRoate.y, _vecRoate.x, _vecRoate.z);	//回転行列の作成関数
	D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//拡大行列の作成関数
	D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//平行移動行列の作成関数

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//行列を結合する関数(第2引数x第3引数=>第1引数に格納)

	//｢D3DTS_WORLD(ワールドトランスフォーム)｣を｢matWorld行列を係数として｣様々な種類の変換を行うことをレンダリングパイプライン/Direct3Dに通知
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//ビュートランスフォーム
	//D3DXVECTOR3...3次の行ベクトル
	//D3DXMATRIXA16...4x4の行列
	//注視点やカメラ位置はメンバのCameraInfoから取ってくる
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
	D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//注視点更新
	lookPos	 = vecLookatPt;

	//プロジェクショントランスフォーム(射影変換)
	D3DXMATRIXA16	matProj;

	//	変更しました	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 0.0f, 200.f);
	//--------------------------------------------------------------------
	
	m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//ライトをあてる　白色で鏡面反射有りに設定
	D3DXVECTOR3	vecDirection(1,1,1);
	D3DLIGHT9		light;
	ZeroMemory(&light,sizeof(D3DLIGHT9) );
	light.Type		= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r	= 1.0f;
	light.Diffuse.g	= 1.0f;
	light.Diffuse.b	= 1.0f;
	light.Specular.r	= 1.0f;
	light.Specular.g	= 1.0f;
	light.Specular.b	= 1.0f;
	light.Ambient.r	= 1.0f;	
	light.Ambient.g	= 1.0f;
	light.Ambient.b	= 1.0f;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	light.Range		= 200.f;
	m_pD3Device->SetLight(0,&light);
	m_pD3Device->LightEnable(0,TRUE);

	//レンダリング
	for (DWORD i=0;	i < MeshInfo[ _id ].dwNumMaterials ; i++)
	{
		m_pD3Device->SetMaterial(&MeshInfo[ _id ].pMeshMaterials[i]);
		m_pD3Device->SetTexture(0,MeshInfo[ _id ].pMeshTextures[i]);
		MeshInfo[ _id ].pMesh->DrawSubset(i);
	}

	
}

/*
	ビルボード用の頂点描画	現在は使用出来ません。ご了承下さい
*/
void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition )
{
	//LPDIRECT3DDEVICE9 m_pD3Device = Getd3Device ();
	//LPDIRECT3DVERTEXBUFFER9 vb;

	//m_pD3Device -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	//m_pD3Device -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	////	頂点バッファをデバイスに設定
	//m_pD3Device -> SetStreamSource( 0, vb, 0, sizeof(VERTEXS) );
	//m_pD3Device -> SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );


	////	頂点バッファのロック
	//VERTEXS* v;

	//if (SUCCEEDED( vb->Lock( 0, 4 * sizeof(VERTEXS), (void**)&v, 0 )))
	//{
	//	//	頂点座標の設定
	//	v[0].x = _vecPosition.x +fWidth/2;
	//	v[0].y = _vecPosition.y +fHeight/2;
	//	v[1].x = _vecPosition.x -fWidth/2;
	//	v[1].y = _vecPosition.y +fHeight/2;
	//	v[2].x = _vecPosition.x -fWidth/2;
	//	v[2].y = _vecPosition.y -fHeight/2;
	//	v[3].x = _vecPosition.x +fWidth/2;
	//	v[3].y = _vecPosition.y -fHeight/2;

	//	//	UV座標
	//	v[0].tu = fTu1;
	//	v[0].tv = fTv1;
	//	v[1].tu = fTu2;
	//	v[1].tv = fTv1;
	//	v[2].tu = fTu2;
	//	v[2].tv = fTv2;
	//	v[3].tu = fTu1;
	//	v[3].tv = fTv2;

	//	//	Z, RHW, 頂点色の設定
	//	for (int i=0; i<4; i++) {
	//		v[i].Z=0;
	//		//v[i].RHW=0; 
	//		v[i].color=D3DCOLOR_ARGB(255,255,255,255);
	//	}

	//	//VERTEXS customVertex9[4] = {
	////		{ _vecPosition.x +fWidth/2,	_vecPosition.y +fHeight/2, _vecPosition.z, 0xff000000, fTu1, fTv1 },	//2
	////		{ _vecPosition.x -fWidth/2,	_vecPosition.y +fHeight/2, _vecPosition.z, 0xff000000, fTu2, fTv1 },	//3
	////		{ _vecPosition.x -fWidth/2,	_vecPosition.y -fHeight/2, _vecPosition.z, 0xff000000, fTu2, fTv2 },	//0
	////		{ _vecPosition.x +fWidth/2,	_vecPosition.y -fHeight/2, _vecPosition.z, 0xff000000, fTu1, fTv2 },	//1
	////	
	////};
	//}
	//D3DXVECTOR3 _vecRotate( 0.f, 0.f, -90.f*D3DX_PI/180.f );
	//D3DXVECTOR3 _vecScall( 1.6f, 1.f, 1.f );

	////ワールドトランスフォーム(絶対座標変換)
	////matWorld->y軸回転
	//D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[最終的なワールドトランスフォーム][平行移動行列を格納する行列]
	//D3DXMatrixIdentity(&matWorld);												//単位行列の作成関数
	//D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRotate.y, _vecRotate.x, _vecRotate.z);	//回転行列の作成関数
	//D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//拡大行列の作成関数
	//D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//平行移動行列の作成関数

	//D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	//D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	//D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//行列を結合する関数(第2引数x第3引数=>第1引数に格納)

	////｢D3DTS_WORLD(ワールドトランスフォーム)｣を｢matWorld行列を係数として｣様々な種類の変換を行うことをレンダリングパイプライン/Direct3Dに通知
	//m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	////ビュートランスフォーム
	////D3DXVECTOR3...3次の行ベクトル
	////D3DXMATRIXA16...4x4の行列
	//D3DXVECTOR3 eyePos	= GetEyePos();
	//D3DXVECTOR3 lookPos	= GetLookPos();
	//float		radian	= GetRad();

	//D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
	//D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
	//D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
	//D3DXMATRIXA16	matView;
	//D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	//m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	////注視点更新
	//lookPos	 = vecLookatPt;

	////プロジェクショントランスフォーム(射影変換)
	//D3DXMATRIXA16	matProj;

	////	変更しました	12/13
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.0f, 200.0f);
	////--------------------------------------------------------------------
	//
	//m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	////ライトをあてる　白色で鏡面反射有りに設定
	//D3DXVECTOR3	vecDirection(1,1,1);
	//D3DLIGHT9		light;
	//ZeroMemory(&light,sizeof(D3DLIGHT9) );
	//light.Type		= D3DLIGHT_DIRECTIONAL;
	//light.Diffuse.r	= 1.0f;
	//light.Diffuse.g	= 1.0f;
	//light.Diffuse.b	= 1.0f;
	//light.Specular.r	= 1.0f;
	//light.Specular.g	= 1.0f;
	//light.Specular.b	= 1.0f;
	//light.Ambient.r	= 1.0f;	
	//light.Ambient.g	= 1.0f;
	//light.Ambient.b	= 1.0f;

	//D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	//light.Range		= 200.f;
	//m_pD3Device->SetLight(0,&light);
	//m_pD3Device->LightEnable(0,TRUE);

	////ワールドトランスフォーム（絶対座標変換）
	//// D3DXMATRIXA16 matWorld,matCurrentView,matPosition;
	//// D3DXMatrixIdentity(&matWorld);
	//// D3DXMatrixTranslation(&matPosition,_vecPosition.x,_vecPosition.y,
	////	 _vecPosition.z);
	//// D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);
	//// 現在のビュー行列を得て、、
	//// m_pD3Device->GetTransform(D3DTS_VIEW,&matCurrentView);
	////  それを逆行列にして、、
	//// D3DXMatrixInverse(&matCurrentView,NULL,&matCurrentView);
	////  ワールド行列に掛け合わせると、ビュー変換を打ち消すことになる
	//// D3DXMatrixMultiply(&matWorld,&matWorld,&matCurrentView);

 ////    m_pD3Device->SetTransform( D3DTS_WORLD, &matWorld );
	//// 
	//// ビュートランスフォーム
	////D3DXVECTOR3...3次の行ベクトル
	////D3DXMATRIXA16...4x4の行列
	////注視点やカメラ位置はcamera.cppから取ってくる
	////D3DXVECTOR3 eyePos	= GetEyePos();
	////D3DXVECTOR3 lookPos	= GetLookPos();
	////float		radian	= GetRad();

	////D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
	////D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
	////D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
	////D3DXMATRIXA16	matView;
	////D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	////m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	////注視点更新
	////lookPos	 = vecLookatPt;

	////プロジェクショントランスフォーム(射影変換)
	////D3DXMATRIXA16	matProj;
	////D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.f, 1.f, 200.f);
	////m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	////ライトをあてる　白色で鏡面反射有りに設定
	////D3DXVECTOR3	vecDirection(1,1,1);
	////D3DLIGHT9		light;
	////ZeroMemory(&light,sizeof(D3DLIGHT9) );
	////light.Type		= D3DLIGHT_DIRECTIONAL;
	////light.Diffuse.r	= 1.0f;
	////light.Diffuse.g	= 1.0f;
	////light.Diffuse.b	= 1.0f;
	////light.Specular.r	= 1.0f;
	////light.Specular.g	= 1.0f;
	////light.Specular.b	= 1.0f;
	////light.Ambient.r	= 1.0f;	
	////light.Ambient.g	= 1.0f;
	////light.Ambient.b	= 1.0f;

	////D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	////light.Range		= 200.f;
	////m_pD3Device->SetLight(0,&light);
	////m_pD3Device->LightEnable(0,TRUE);

	////_vecPosition.z = -0.5f;

	////VERTEXS* pVertex;

	////m_pD3Device -> CreateVertexBuffer( sizeof(VERTEXS) * 4, 0, D3DFVF, D3DPOOL_MANAGED, &vb, NULL);
	////vb->Lock(0,0,(void **)&pVertex,0);
	////memcpy(pVertex,customVertex9,sizeof(VERTEXS) * 4);
	////vb->Unlock();

	//
	//TEXTUREINFO* TextureInfo = GetTextInfo();

	//m_pD3Device -> SetTexture ( 0, TextureInfo[_id].pTexture );
	//m_pD3Device -> DrawPrimitive(D3DPT_TRIANGLEFAN,0,2);

	//m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/*
	3Dアニメーション付き描画処理
*/
void CRenderManager::AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall )
{

	//ワールドトランスフォーム(絶対座標変換)
	//matWorld->y軸回転
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[最終的なワールドトランスフォーム][平行移動行列を格納する行列]
	D3DXMatrixIdentity(&matWorld);												//単位行列の作成関数
	D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRoate.y, _vecRoate.x, _vecRoate.z);	//回転行列の作成関数
	D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//拡大行列の作成関数
	D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//平行移動行列の作成関数

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//行列を結合する関数(第2引数x第3引数=>第1引数に格納)

	//｢D3DTS_WORLD(ワールドトランスフォーム)｣を｢matWorld行列を係数として｣様々な種類の変換を行うことをレンダリングパイプライン/Direct3Dに通知
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//ビュートランスフォーム
	//D3DXVECTOR3...3次の行ベクトル
	//D3DXMATRIXA16...4x4の行列
	//注視点やカメラ位置はメンバのCameraInfoから取ってくる
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
	D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//注視点更新
	lookPos	 = vecLookatPt;

	//プロジェクショントランスフォーム(射影変換)
	D3DXMATRIXA16	matProj;

	//	変更しました	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
	//--------------------------------------------------------------------
	
	m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//ライトをあてる　白色で鏡面反射有りに設定
	D3DXVECTOR3	vecDirection(1,1,1);
	D3DLIGHT9		light;
	ZeroMemory(&light,sizeof(D3DLIGHT9) );
	light.Type		= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r	= 1.0f;
	light.Diffuse.g	= 1.0f;
	light.Diffuse.b	= 1.0f;
	light.Specular.r	= 1.0f;
	light.Specular.g	= 1.0f;
	light.Specular.b	= 1.0f;
	light.Ambient.r	= 1.0f;	
	light.Ambient.g	= 1.0f;
	light.Ambient.b	= 1.0f;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	light.Range		= 200.f;
	m_pD3Device->SetLight(0,&light);
	m_pD3Device->LightEnable(0,TRUE);

	LPD3DXMATRIX _World = &matWorld;

	AllocateHierarchy[ _id ].SetWorld( _World );

	AllocateHierarchy[ _id ].Draw( m_pD3Device );
}

/*
	スクリーン座標をワールド座標に変換
*/
D3DXVECTOR3* CRenderManager::CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	スクリーン座標内ｘ
   int Sy,				//	スクリーン座標内ｙ
   float fZ,			//	射影空間でのZ値（0～1）
   int Screen_w,		//	スクリーンの横幅
   int Screen_h,		//	スクリーンの縦幅
   D3DXMATRIXA16* View,	//	ビュー行列
   D3DXMATRIXA16* Prj	//	射影変換行列
)
{
   // 各行列の逆行列を算出
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // 逆変換
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}

/*
	スクリーン座標内のマウス座標をワールド座標に変換
*/
void CRenderManager::MousePosTransform( long _cursorMovePosX, long _cursorMovePosY )
{
	D3DXMATRIXA16	matView;
	D3DXMATRIXA16	matProj;

	D3DXVECTOR3	vecEyePt	( GetEyePos() );	//カメラ(視点)位置
	D3DXVECTOR3	vecLookatPt	( GetLookPos() );	//注視位置
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);	//上方位置

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);

	CalcScreenToWorld ( &vecCursorPos, _cursorMovePosX, _cursorMovePosY, 
						1.f, static_cast<int>(WIDTH), static_cast<int>(HEIGHT), &matView, &matProj );

	char msg[256];
	ZeroMemory(msg, sizeof(msg));
	sprintf_s(msg, "vecCursorPos x = %f, y = %f, z = %f\n", vecCursorPos.x, vecCursorPos.y, vecCursorPos.z);
	OutputDebugStringA(msg);
}