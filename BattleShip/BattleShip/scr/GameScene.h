/**
*@file	GameScene.h
*@author	�T�c
*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_


#include "SceneInterface.h"
#include "StateManager.h"
#include "StageObject.h"
#include "Player.h"

/**
*@brief	�퓬�V�[���N���X
*@details	�V�[����{�N���X(CScene)��h�������N���X�B@n
			Init�AControl�ADraw�ARender�֐������C�u�����̃T�u���[�`�����ŌĂ΂��̂ŁA�錾���邱�ƁB@n
			�����2D�`��݂̗̂\��Ȃ̂�Render�֐��͐錾�����Ă��邪�A���g�͂Ȃ��B
*/
class GameScene : public CScene
{
private:
	StateManager	m_stateManager;	///<	�퓬���ł̃X�e�[�g���Ǘ�����I�u�W�F�N�g
	Player			m_Player[_PLAYER_NUM_];		///<	�v���C���[�N���X
	StageObject		m_stageObject;		///<	�X�e�[�W�I�u�W�F�N�g
	int const		m_playerID;			///<	�N�����̃v���C���[ID

public:
	/**
	*@brief	�R���X�g���N�^
	*@details	�g��Ȃ��Ǘ��|�C���^������ꍇNULL�|�C���^������
	*@param[in]	_id	�������g�̃V�[��ID
	*@param[in]	_playerID	�N�����̃v���C���[ID
	*@param[in]	_pRenderManager	3D�`��Ǘ��̃|�C���^
	*@param[in]	_pDrawManager	2D�`��Ǘ��̃|�C���^
	*@param[in]	_pKey			�L�[�Ǘ��̃|�C���^
	*@param[in]	m_pMouse		�}�E�X�Ǘ��̃|�C���^
	*/
	GameScene(int _id, int _playerID, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager,
		CKey* const _pKey, CMouse* const m_pMouse );

	/**
	*@brief	������
	*@param[in]	_playerID	�N�����̃v���C���[ID
	*/
	bool Init();

	/**
	*@brief	���[�`������
	*/
	int	 Control();

	/**
	*@brief	2D�`��
	*/
	void Draw();
	void Render(){};
};

#endif