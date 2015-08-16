/**
*@file	SceneManager.h
*@author	�T�c
*@brief	�V�[���Ǘ�
*/


#ifndef _SCENEMANAGE_H_
#define _SCENEMANAGE_H_

#include "RenderManager.h"
#include "DrawManager.h"
#include "device.h"
#include "../../BattleShip/scr/SceneInterface.h"
#include "Key.h"
#include "Mouse.h"
#include "joystick_XInput.h"


/**
*@brief	�V�[���Ǘ��N���X
*@details	�Ǘ��N���X������A��������e�V�[���N���X�𐶐����j�����J��Ԃ��B
*/
class CSceneManager
{
public:
	/**
	*@brief	�V�[���ԍ�
	*/
	enum SCENE_NUM
	{
		SCENE_NONE = -1,
		//SCENE_LOGO,
		SCENE_TITLE,
		//SCENE_SELECT,
		SCENE_BATTLE,
		//SCENE_RESULT,
		SCENE_MAX
	};

private:
	CScene*			m_sceneObj;			///<	�V�[���I�u�W�F�N�g�|�C���^
	CDevice* const	m_pDevice;			///<	�f�o�C�X�N���X�|�C���^
	CRenderManager* m_pRenderManager;	///<	3D�`��I�u�W�F�N�g�|�C���^
	CDrawManager*	m_pDrawManager;		///<	2D�`��I�u�W�F�N�g�|�C���^
	CKey*			m_pKey;				///<	�L�[�Ǘ��N���X�I�u�W�F�N�g�|�C���^
	CMouse*			m_pMouse;			///<	�}�E�X�Ǘ��N���X�I�u�W�F�N�g�|�C���^
	CXInput*		m_pXInput;		///<�W���C�X�e�B�b�N�Ǘ��N���X

	int		iCurrentScene;		///<	���̃V�[��
	bool	bChangeSceneFlag;	///<	�V�[���ύX�t���O
	bool	m_bRenderType;		///<	�`��^�C�v�̔���

public:	
	/**
	*@brief	 �R���X�g���N�^
	*/
	CSceneManager( int _scene , CDevice* const _pDevice, bool _bRenderType );	//	�R���X�g���N�^

public:
	/**
	*@brief	 �Q�[�����C���֐�
	*/
	int GameMain ();
		
	/**
	*@brief	 �V�[���N���X�̃��[�`���̐���
	*/
	void SceneRoutingManage ();
	
	/**
	*@brief	�`��̊Ǘ�
	*@param[in]	b3dView	3D���f������������true�ɁB
	*/
	void ViewManage ( bool b3dView = false );
	
	/**
	*@brief	 �����_�����O�Ǘ�(3D)
	*/
	void RenderManage ();
	
	/**
	*@brief	 �`��Ǘ�(2D)
	*@param[in]	_b3dView�@3D�`��������ɂ��邩���f����
	*/
	void DrawManage ( bool _b3dView );

	/**
	*@brief	 �`��㏈��
	*/
	void EndRender ();

public:
	/**
	*@brief	���̃V�[����Ԃ��擾
	*@return	iCurrentScene	���݂̃V�[��
	*/
	int	CSceneManager::GetCurrentScene() { return iCurrentScene; }
	/**
	*@brief	�V�[���ύX�t���O���擾
	*@return	bChangeSceneFlag	�V�[���ύX�t���O
	*/
	bool CSceneManager::GetChangeSceneFlag() { return  bChangeSceneFlag; }
	
	/**
	*@brief	�V�[���ύX�t���O�̍X�V
	*@param[in]	_bTemp	�V�[���ύX�t���O�𗧂Ă�
	*/
	void CSceneManager::UpdateChangeFlag( bool _bTemp ) { bChangeSceneFlag = _bTemp; }


public:
	/**
	*@brief	 �V�[���Ǘ�
	*@todo	���̊֐��̓Q�[�����Őݒ肵�Ă��ׂ�
	*/
	virtual void Manage ();

	/**
	*@brief	�V�[���I�u�W�F�N�g�̉��
	*@todo	SceneManager���ɉ�����Ȃ��Ƃ����Ȃ������o��ǉ������ꍇ�́A@n
			���̂��тɒǉ����Ă��B
	*/
	virtual bool DeleteSceneObj();
};

#endif
