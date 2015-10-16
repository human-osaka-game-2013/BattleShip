/**
*@file	RenderManager.h
*@author	�T�c
*/

#ifndef _RENDER_MANAGE_H_
#define _RENDER_MANAGE_H_

#include "device.h"
#include "AllocateHierarchy.h"
#include "gameObject.h"

#include "Window.h"

//	���b�V���f�[�^
struct MESH_INFO
{
	LPD3DXMESH			pMesh;			//	���b�V���f�[�^�̊i�[
	D3DMATERIAL9*		pMeshMaterials;	//	�}�e���A���̃f�[�^
	LPDIRECT3DTEXTURE9*	pMeshTextures;	//	�e�N�X�`���̃f�[�^
	DWORD				dwNumMaterials;	//	
};

//	�J�������
struct CAMERA_INFO
{
	D3DXVECTOR3 eyePos;		// ���_���Wxyz
	D3DXVECTOR3 lookPos;	// �����_���Wxyz
	float		radian;		// ���_��]�␳�x
};

/**
*@brief	3D�`��N���X
*@details	�V�[���Ǘ��N���X�Ɏ��̂��������A�e�V�[���N���X�Ƀ|�C���^��n���B	
*@todo	�A�h���X��const�ɂ���̂͏��߂ĂȂ̂ŁA�C������\��������B
*/
class CRenderManager
{
public:
	//	�g�p���郁�b�V���t�@�C����ID�Ƃ��ė�
	enum MESH_ID
	{
		MESH_BG1,

		MESH_BOX_1,

		MESH_BULLET,

		MESH_MAX
	};

	//	�g�p����A�j���[�V�����t�����b�V���t�@�C����
	//	ID�Ƃ��ė�
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

	//	�A�j���[�V�����t�����b�V���f�[�^�ۑ��ϐ�
	CAllocateHierarchy AllocateHierarchy[ AN_MESH_MAX ];

private:
	MESH_INFO MeshInfo[ MESH_MAX ];	//	���b�V���f�[�^�ۑ��p�����o�ϐ�

	CAMERA_INFO CameraInfo;		//	�J�������ۑ��p�����o�ϐ�

	IDirect3DDevice9* const	m_pD3Device;	///<D3D�f�o�C�X
	IDirectInputDevice8* const m_pMouseDevice;	///<�}�E�X�f�o�C�X(�}�E�X���W�̕ϊ��ɕK�v)

public:
	/**
	*@brief	�R���X�g���N�^
	*@param[in]	_pD3Device	
	*/
	CRenderManager( IDirect3DDevice9* const _pD3Device, 
					IDirectInputDevice8* const _pMouseDevice );

	/**
	*@brief	�f�X�g���N�^
	*/
	~CRenderManager();

	/**
	*@brief	���_���W�̎擾
	*@return CameraInfo.eyePos
	*/
	D3DXVECTOR3 GetEyePos() { return CameraInfo.eyePos; }
	
	/**
	*@brief	�����_���W�̎擾
	*@return CameraInfo.lookPos
	*/
	D3DXVECTOR3 GetLookPos(){ return CameraInfo.lookPos; }
	
	/**
	*@brief	���_��]�␳�x�̎擾
	*@return CameraInfo.radian
	*/
	float GetRad()	{ return CameraInfo.radian; }

public:
	

	/*
		�r���{�[�h�p�̒��_�`��
	*/
	void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition );
	
	//	3D�`�揈��
	void Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	//	3D�A�j���[�V�����t���`�揈��
	void AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	

	// �X�N���[�����W�����[���h���W�ɕϊ�
	D3DXVECTOR3* CalcScreenToWorld
	(
	   D3DXVECTOR3* pout,	
	   int Sx,				//	�X�N���[�����W����
	   int Sy,				//	�X�N���[�����W����
	   float fZ,			//	�ˉe��Ԃł�Z�l�i0�`1�j
	   int Screen_w,		//	�X�N���[���̉���
	   int Screen_h,		//	�X�N���[���̏c��
	   D3DXMATRIXA16* View,	//	�r���[�s��
	   D3DXMATRIXA16* Prj		//	�ˉe�ϊ��s��
	);

	/**
	*@brief	�X�N���[�����W���̃}�E�X���W�����[���h���W�ɕϊ�
	*@param[in]	_cursorMovePosX	�}�E�X�ړ���X�BCMouse�N���X����擾
	*@param[in]	_cursorMovePosY	�}�E�X�ړ���Y�BCMouse�N���X����擾
	*/
	void MousePosTransform( long _cursorMovePosX, long _cursorMovePosY );

public:
	/**
	*@brief	3D�`��O����
	*/
	void BeginRender();

	//	x�t�@�C���ǂݍ���
	//	(in)���b�V���t�@�C����ID�C�t�@�C���A�h���X (out)�ǂݍ��ݐ�����true	���s��false
	bool LoadXFile( MESH_ID _id, LPCSTR _xFileName );

	//	�J������񏉊���
	void CameraInit();

	//	���b�V���f�[�^�̉��
	void ReleaseMesh( int _id );

	//	�S���b�V���f�[�^�����
	void AllReleaseMesh();

public:
	//	
	virtual bool AllLoadXFile();
};

#endif