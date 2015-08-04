#ifndef _SCENE_H_
#define _SCENE_H_
#include "RenderManager.h"
#include "DrawManager.h"
#include "Key.h"
#include "Mouse.h"
#include "gameObject.h"
#include <list>

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
	*@param[in]	m_pMouse		�}�E�X�Ǘ��̃|�C���^
	*/
	CScene( int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager,
		CKey* const _pKey, CMouse* const m_pMouse );
	/**
	*@brief�f�X�g���N�^
	*/
	~CScene();
public:
	virtual bool Init() = 0;		///< �������̉��z�֐�
	virtual int	 Control()	= 0;	///< �����̉��z�֐��B@n
									///	GetSceneID()�ŃV�[��ID��Ԃ��āA�}�l�[�W���[�̕��ŃV�[���ύX�Ɏg�킹��
	virtual void Draw()	= 0;		///< 2D�`��̉��z�֐�
	virtual void Render() = 0;		///< 3D�`��̉��z�֐�

public:
	/**
	*@brief	�V�[��ID���擾
	*@return	m_sceneID	�����̃V�[��ID���擾
	*/
	int GetSceneID()	{ return m_sceneID; }	

};

#endif