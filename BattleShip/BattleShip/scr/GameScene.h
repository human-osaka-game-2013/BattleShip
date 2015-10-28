/**
*@file	GameScene.h
*@author	�T�c
*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "Connect.h"
#include <new>
#include <vector>

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
public:
	/**
	*@brief	�Ֆʂ̃t���[���I�u�W�F�N�g�N���X
	*/
	class Background : public CGameObject
	{
	private:
		float fWidth ,fHeight;

	public:
		/**
		*@brief	������
		*/
		void Init()
		{
			SetPosition(0.f, 0.f, 0.5f);
			fHeight = HEIGHT;
			fWidth = WIDTH;
		}
		void Control(){};
		void Draw(){};
		void Free(){};
		float GetWidth(){ return fWidth; }
		float GetHeight(){ return fHeight; }
	};

private:
	StateManager*	m_stateManager;		///<	�퓬���ł̃X�e�[�g���Ǘ�����I�u�W�F�N�g
	std::vector<Player*>	m_Player;	///<	�v���C���[�N���X
	StageObject*	m_pStageObject;		///<	�X�e�[�W�I�u�W�F�N�g
	int				m_playerID;			///<	�N�����̃v���C���[ID
	Background		m_background;		///<	�w�i�I�u�W�F�N�g
	Connect			m_Connect;			///<	�ʐM�f�o�C�X�N���X

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
	GameScene(int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse)
		: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse)
	{
		
	}
	
	/**	
	*@brief �������
	*/
	bool Free();

public:
	
	/**
	*@brief	�Q�[�����C���̏������֐�
	*@return	�������̌���
	*@retval true	����
	*@retval false	�������ɉ��炩�̎��s���������ꍇ
	*/
	bool Init();

	/**
	*@brief	�Q�[�����C���̊�{�����̊֐�
	*@return	�V�[���ύX�����锻�f�̒l
	*@retval 0	�V�[���ύX����
	*@retval 1	�V�[���ύX�L��
	*/
	int	 Control();

	/**
	*@brief	2D�`��
	*/
	void Draw();
	void Render(){};

private:
	/**
	*@brief	�ʐM����
	*@details	Connect�N���X�����o���g�p���āA���葤�̃f�[�^�Ƃ̂����������ōs��
	*@retval true	����Ƀf�[�^�̂���肪�s��ꂽ
	*@retval false	�f�[�^�̂���肪���s����
	*/
	bool CommunicationProcessing();
};

#endif