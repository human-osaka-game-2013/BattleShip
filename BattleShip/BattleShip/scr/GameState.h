/**
*@file	GameState.h
*@author	�T�c
*/

#ifndef	_GAMESTATE_H_
#define _GAMESTATE_H_

#include "Player.h"
#include "StageObject.h"
#include "DrawManager.h"
#include "Mouse.h"

class GameState
{
public:
	/**
	*@brief	�Q�[�����ł̃X�e�[�g�p�^�[���̗񋓁B
	*@details	��ɃX�e�[�g�؂�ւ����Ɏg�p
	*/
	enum	_STATE_NUM_
	{
		STATE_NONE,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

protected:
	_STATE_NUM_ m_stateID;	///<	���g�̃X�e�[�g��ID	
	Player* m_pPlayer[_PLAYER_NUM_];	///<	��f�[�^�i�[�p
	StageObject* m_pStage;	///<	�X�e�[�W�f�[�^�i�[�p
	int m_playerID;
	
//	�f�o�C�X
protected:
	CDrawManager*	m_pDrawManager;	///<	2D�`��Ǘ��N���X�|�C���^(const�|�C���^)
	CMouse*			m_pMouse;		///<	�}�E�X�Ǘ��N���X�|�C���^(const�|�C���^)

public:
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̏�����
	*/
	virtual bool Init() = 0;

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̃T�u���[�`������
	*/
	virtual bool Control() = 0;

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̕`��
	*/
	virtual void Draw() = 0;

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̒ʐM���̃T�u���[�`������
	*/
	virtual void ComStandby() = 0;

	/**
	*@brief	�X�e�[�g��ID�擾
	*/
	_STATE_NUM_ GetState(){ return m_stateID; }

	/**
	*@brief	�v���C���[�N���X�|�C���^���Z�b�g
	*@param[in]	_pPlayer	�v���C���[�I�u�W�F�N�g�|�C���^
	*@param[in]	_playerID	���Ԃ̃v���C���[��
	*/
	void SetPlayerPtr( Player* _pPlayer, int _playerID ){ 
		m_pPlayer[_playerID] = _pPlayer;
	}

	/**
	*@brief	�X�e�[�W�N���X�|�C���^���Z�b�g
	*@param[in]	_pPlayer	�X�e�[�W�N���X�|�C���^��
	*@param[in]	_playerID	���Ԃ̃v���C���[��
	*/
	void SetStagePtr( StageObject* _pStage ){ 
		m_pStage = _pStage;
	}

	/**
	*@brief	�`��N���X�Z�b�g
	*/
	void SetDraw( CDrawManager* const _pDrawManager ){
		m_pDrawManager = _pDrawManager;
	}

	/**
	*@brief	�}�E�X�N���X�Z�b�g
	*/
	void SetMouse( CMouse* const _pMouse ){
		m_pMouse = _pMouse;
	}

	/**
	*@brief	�v���C���[ID�Z�b�g
	*/
	void SetPlayerID( int _playerID ){ m_playerID = _playerID; }
};

#endif