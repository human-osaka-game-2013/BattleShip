/**
*@file	SceneInterface.h
*@author	�T�c
*/

#ifndef _SCENE_H_
#define _SCENE_H_
#include "RenderManager.h"
#include "DrawManager.h"
#include "Key.h"
#include "Mouse.h"
#include "gameObject.h"
#include <list>

#define _PLAYER_ID_	1

class CScene
{
protected:
	CRenderManager* const m_pRenderManager;	///<	3D�`��Ǘ��N���X�|�C���^(const�|�C���^)
	CDrawManager*	const m_pDrawManager;	///<	2D�`��Ǘ��N���X�|�C���^(const�|�C���^)
	CKey*			const m_pKey;			///<	�L�[�Ǘ��N���X�|�C���^	(const�|�C���^)
	CMouse*			const m_pMouse;			///<	�}�E�X�Ǘ��N���X�|�C���^(const�|�C���^)
	
protected:
	int m_sceneID;	//	�V�[��ID�ۑ��ϐ�(�R���X�g���N�^�̎��ɃV�[��ID������)
	int m_count;	//	�V�[�����ł̃J�E���g

public:
	/**
	*@brief	�R���X�g���N�^
	*@details	�g��Ȃ��Ǘ��|�C���^������ꍇNULL�|�C���^������
	*@param[in]	_id	�������g�̃V�[��ID
	*@param[in]	_pRenderManager	3D�`��Ǘ��̃|�C���^
	*@param[in]	_pDrawManager	2D�`��Ǘ��̃|�C���^
	*@param[in]	_pKey			�L�[�Ǘ��̃|�C���^
	*@param[in]	_pMouse		�}�E�X�Ǘ��̃|�C���^
	*/
	CScene( int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager,
		CKey* const _pKey, CMouse* const _pMouse);
	/**
	*@brief�f�X�g���N�^
	*/
	virtual ~CScene()
	{
		
	}

public:
	/**
	*@brief	�������̏������z�֐�
	*@return	�������̌���
	*@retval true	����
	*@retval false	�������ɉ��炩�̎��s���������ꍇ
	*/
	virtual bool Init() = 0;

	/**
	*@brief	�V�[���̊�{�����̏������z�֐�
	*@return	�V�[���ύX�����锻�f�̒l
	*@retval 0	�V�[���ύX����
	*@retval 1	�V�[���ύX�L��
	*/
	virtual int	 Control()	= 0;	

	virtual void Draw()	= 0;		///< 2D�`��̉��z�֐�
	virtual void Render() = 0;		///< 3D�`��̉��z�֐�

public:
	/**
	*@brief	�V�[��ID���擾
	*@return	m_sceneID	�����̃V�[��ID���擾
	*/
	int GetSceneID()	{ return m_sceneID; }	

	/**
	*@brief	�V�[��ID���X�V
	*/
	void SetSceneID( int _scene ){ m_sceneID = _scene; }
};

#endif