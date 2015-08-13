/**
*@file	StateManager.cpp
*@author	�T�c
*/
#include <windows.h>	//window��b�t�@�C��
#include "StateManager.h"
#include "lib_head.h"

//--------�X�e�[�g�p�^�[���N���X�̃w�b�_�[-------
#include "SetShip.h"
#include "Selection.h"
#include "Result.h"
#include "StageEffect.h"
//-------------------------------------------

#define _FIRST_SETATE_ StateManager::STATE_SET_SHIP	///<	�ŏ��̃X�e�[�g�p�^�[��

//	�R���X�g���N�^
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, StageObject* const	_pStageObject) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject)
{
	StateInit();
}

//	�X�e�[�g�̏�����
void StateManager::StateInit()
{
	m_beforeState = STATE_NONE;		///<	�������Ȃ̂ňȑO�̃X�e�[�g�͂������������ׁASTATE_NONE�ɁB
	m_currentState = _FIRST_SETATE_;///<	�X�e�[�g�̏������Ȃ̂ōŏ��ɓǂݍ��ނł��낤�p�^�[���̒萔������
	ChangeState(m_currentState);	///<	�܂��X�e�[�g�|�C���g�ɂ͉��������Ă��Ȃ��̂ŏ����������˂�
}

//	�X�e�[�g�̊�{���[�`������
void StateManager::StateCotrol()
{
	m_beforeState = m_currentState;	///<	���[�`���I�ɂȏ����őO�t���[�����̃X�e�[�g�����݂̃X�e�[�g�ɍ��킹��B

	if( m_pGameState->Control() )	///<	�X�e�[�g�̃��[�`�������̌��ʃV�[�����ς��K�v�������
	{
		switch( m_currentState )	///<	�ύX����X�e�[�g�͏��Ԃ�������x���܂��Ă���̂ŕ���
		{
		case STATE_SET_SHIP:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_SELECTION:
			ChangeState(STATE_RESULT);

			break;
		case STATE_RESULT:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_STAGE_EFFECT:
			//ChangeState(STATE_SELECTION);
			//
			break;
		}
	}


}

//	�X�e�[�g�̊�{�`��
void StateManager::StateDraw()
{
	m_pGameState->Draw();
}


//	�X�e�[�g�p�^�[���̐؂�ւ�
bool StateManager::ChangeState( _STATE_NUM_ _stateType )
{
	if( _stateType > STATE_STAGE_EFFECT&& _stateType < STATE_SET_SHIP )
	{
		MessageBoxA(0,"�X�e�[�g�p�^�[���̕ύX�Ɏ��s���܂����I\n�������m�F���ĉ������I(����;)",NULL,MB_OK);
		return false;
	}
	
	switch( _stateType )
	{
	StateDelete();

	case STATE_SET_SHIP:
		m_pGameState = new SetShip();

		break;
	case STATE_SELECTION:
		m_pGameState = new Selection();

		break;
	case STATE_RESULT:
		m_pGameState = new Result();

		break;
	case STATE_STAGE_EFFECT:
		m_pGameState = new StageEffect();

		break;
	}
	m_currentState = _stateType;

	return true;
}

//	�X�e�[�g�I�u�W�F�N�g�̏���
void StateManager::StateDelete()
{
	CLASS_DELETE(m_pGameState);
}

StateManager::~StateManager()
{
	delete m_pGameState;
}