#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"

class StateManager
{
public:
	/**
	*@brief	�퓬�X�e�[�g�p�^�[���̗�
	*/
	enum _STATE_NUM_
	{
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

private:
	GameState*		m_pGameState;	///<	�퓬�X�e�[�g�p�^�[���I�u�W�F�N�g�̃|�C���^
	_STATE_NUM_		m_beforeState;	///<	�ȑO�̃X�e�[�g�p�^�[��
	_STATE_NUM_		m_currentState;	///<	���݂̃X�e�[�g�p�^�[��
	Player* const 	m_pPlayer1;		///<	�v���C���[1���i�[�|�C���^
	Player* const 	m_pPlayer2;		///<	�v���C���[2���i�[�|�C���^
	StageObject* const	m_pStageObject;	///<	�X�e�[�W���i�[�|�C���^

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	StateManager( Player* const _pPlayer1, Player* const _pPlayer2,
		StageObject* const	_pStageObject);

	/**
	*@brief	�X�e�[�g�p�^�[���̐؂�ւ�
	*param[in]	_stateType	
	*/
	void ChangeState( _STATE_NUM_ _stateType );
	
	void Init();
	void Cotrol();
	void Draw();

};


#endif