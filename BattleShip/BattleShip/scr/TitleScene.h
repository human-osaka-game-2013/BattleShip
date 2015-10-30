/**
*@file	TitleScene.h
*@author	�T�c
*/

#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "SceneInterface.h"
#include "Background.h"


class TitleScene : public CScene
{
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
	TitleScene(int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse)
		: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse)
	{
		
	}


};

#endif