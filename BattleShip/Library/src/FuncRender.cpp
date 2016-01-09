/**
*@file	FuncRender.cpp
*@author	�T�c
*@brief	3D�`��n�֐��܂Ƃ�
*/

#include "RenderManager.h"


/*
	3D�`�揈��
*/
void CRenderManager::Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall )
{

	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld, matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRoate.y, _vecRoate.x, _vecRoate.z);	//��]�s��̍쐬�֐�
	D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//�g��s��̍쐬�֐�
	D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	//�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//�r���[�g�����X�t�H�[��
	//D3DXVECTOR3...3���̍s�x�N�g��
	//D3DXMATRIXA16...4x4�̍s��
	//�����_��J�����ʒu�̓����o��CameraInfo�������Ă���
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//�����_�X�V
	lookPos	 = vecLookatPt;

	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMATRIXA16	matProj;

	//	�ύX���܂���	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 0.0f, 200.f);
	//--------------------------------------------------------------------
	
	m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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

	//�����_�����O
	for (DWORD i=0;	i < MeshInfo[ _id ].dwNumMaterials ; i++)
	{
		m_pD3Device->SetMaterial(&MeshInfo[ _id ].pMeshMaterials[i]);
		m_pD3Device->SetTexture(0,MeshInfo[ _id ].pMeshTextures[i]);
		MeshInfo[ _id ].pMesh->DrawSubset(i);
	}

	
}

/*
	�r���{�[�h�p�̒��_�`��	���݂͎g�p�o���܂���B������������
*/
void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition )
{
	//LPDIRECT3DDEVICE9 m_pD3Device = Getd3Device ();
	//LPDIRECT3DVERTEXBUFFER9 vb;

	//m_pD3Device -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	//m_pD3Device -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	////	���_�o�b�t�@���f�o�C�X�ɐݒ�
	//m_pD3Device -> SetStreamSource( 0, vb, 0, sizeof(VERTEXS) );
	//m_pD3Device -> SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );


	////	���_�o�b�t�@�̃��b�N
	//VERTEXS* v;

	//if (SUCCEEDED( vb->Lock( 0, 4 * sizeof(VERTEXS), (void**)&v, 0 )))
	//{
	//	//	���_���W�̐ݒ�
	//	v[0].x = _vecPosition.x +fWidth/2;
	//	v[0].y = _vecPosition.y +fHeight/2;
	//	v[1].x = _vecPosition.x -fWidth/2;
	//	v[1].y = _vecPosition.y +fHeight/2;
	//	v[2].x = _vecPosition.x -fWidth/2;
	//	v[2].y = _vecPosition.y -fHeight/2;
	//	v[3].x = _vecPosition.x +fWidth/2;
	//	v[3].y = _vecPosition.y -fHeight/2;

	//	//	UV���W
	//	v[0].tu = fTu1;
	//	v[0].tv = fTv1;
	//	v[1].tu = fTu2;
	//	v[1].tv = fTv1;
	//	v[2].tu = fTu2;
	//	v[2].tv = fTv2;
	//	v[3].tu = fTu1;
	//	v[3].tv = fTv2;

	//	//	Z, RHW, ���_�F�̐ݒ�
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

	////���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	////matWorld->y����]
	//D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	//D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	//D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRotate.y, _vecRotate.x, _vecRotate.z);	//��]�s��̍쐬�֐�
	//D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//�g��s��̍쐬�֐�
	//D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	//D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	//D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	//D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	////�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	//m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	////�r���[�g�����X�t�H�[��
	////D3DXVECTOR3...3���̍s�x�N�g��
	////D3DXMATRIXA16...4x4�̍s��
	//D3DXVECTOR3 eyePos	= GetEyePos();
	//D3DXVECTOR3 lookPos	= GetLookPos();
	//float		radian	= GetRad();

	//D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	//D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	//D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	//D3DXMATRIXA16	matView;
	//D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	//m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	////�����_�X�V
	//lookPos	 = vecLookatPt;

	////�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	//D3DXMATRIXA16	matProj;

	////	�ύX���܂���	12/13
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.0f, 200.0f);
	////--------------------------------------------------------------------
	//
	//m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	////���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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

	////���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	//// D3DXMATRIXA16 matWorld,matCurrentView,matPosition;
	//// D3DXMatrixIdentity(&matWorld);
	//// D3DXMatrixTranslation(&matPosition,_vecPosition.x,_vecPosition.y,
	////	 _vecPosition.z);
	//// D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);
	//// ���݂̃r���[�s��𓾂āA�A
	//// m_pD3Device->GetTransform(D3DTS_VIEW,&matCurrentView);
	////  ������t�s��ɂ��āA�A
	//// D3DXMatrixInverse(&matCurrentView,NULL,&matCurrentView);
	////  ���[���h�s��Ɋ|�����킹��ƁA�r���[�ϊ���ł��������ƂɂȂ�
	//// D3DXMatrixMultiply(&matWorld,&matWorld,&matCurrentView);

 ////    m_pD3Device->SetTransform( D3DTS_WORLD, &matWorld );
	//// 
	//// �r���[�g�����X�t�H�[��
	////D3DXVECTOR3...3���̍s�x�N�g��
	////D3DXMATRIXA16...4x4�̍s��
	////�����_��J�����ʒu��camera.cpp�������Ă���
	////D3DXVECTOR3 eyePos	= GetEyePos();
	////D3DXVECTOR3 lookPos	= GetLookPos();
	////float		radian	= GetRad();

	////D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	////D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	////D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	////D3DXMATRIXA16	matView;
	////D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	////m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	////�����_�X�V
	////lookPos	 = vecLookatPt;

	////�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	////D3DXMATRIXA16	matProj;
	////D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.f, 1.f, 200.f);
	////m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	////���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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
	3D�A�j���[�V�����t���`�揈��
*/
void CRenderManager::AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall )
{

	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRoate.y, _vecRoate.x, _vecRoate.z);	//��]�s��̍쐬�֐�
	D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//�g��s��̍쐬�֐�
	D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	//�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//�r���[�g�����X�t�H�[��
	//D3DXVECTOR3...3���̍s�x�N�g��
	//D3DXMATRIXA16...4x4�̍s��
	//�����_��J�����ʒu�̓����o��CameraInfo�������Ă���
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	m_pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//�����_�X�V
	lookPos	 = vecLookatPt;

	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMATRIXA16	matProj;

	//	�ύX���܂���	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
	//--------------------------------------------------------------------
	
	m_pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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
	�X�N���[�����W�����[���h���W�ɕϊ�
*/
D3DXVECTOR3* CRenderManager::CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	�X�N���[�����W����
   int Sy,				//	�X�N���[�����W����
   float fZ,			//	�ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,		//	�X�N���[���̉���
   int Screen_h,		//	�X�N���[���̏c��
   D3DXMATRIXA16* View,	//	�r���[�s��
   D3DXMATRIXA16* Prj	//	�ˉe�ϊ��s��
)
{
   // �e�s��̋t�s����Z�o
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}

/*
	�X�N���[�����W���̃}�E�X���W�����[���h���W�ɕϊ�
*/
void CRenderManager::MousePosTransform( long _cursorMovePosX, long _cursorMovePosY )
{
	D3DXMATRIXA16	matView;
	D3DXMATRIXA16	matProj;

	D3DXVECTOR3	vecEyePt	( GetEyePos() );	//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( GetLookPos() );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);	//����ʒu

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);

	CalcScreenToWorld ( &vecCursorPos, _cursorMovePosX, _cursorMovePosY, 
						1.f, static_cast<int>(WIDTH), static_cast<int>(HEIGHT), &matView, &matProj );

	char msg[256];
	ZeroMemory(msg, sizeof(msg));
	sprintf_s(msg, "vecCursorPos x = %f, y = %f, z = %f\n", vecCursorPos.x, vecCursorPos.y, vecCursorPos.z);
	OutputDebugStringA(msg);
}