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
#define _POS_PLAYER1FRAME_	0.f, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)						///<�v���C���[1���̘g�̕\�����W
#define _POS_PLAYER2FRAME_	_BLOCK_WIDTH_SIZE_*12, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)	///<�v���C���[2���̘g�̕\�����W
#define _SIZE_PLAYERFRAME_	_BLOCK_WIDTH_SIZE_*11, _BLOCK_HEIGHT_SIZE_*5	///<�v���C���[���̘g�T�C�Y

//	�R���X�g���N�^ 
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, 
							StageObject* const _pStageObject, const int _playerID) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject), m_playerID(_playerID)
{
	StateInit();
}

//	�X�e�[�g�̏�����
void StateManager::StateInit()
{
	m_beforeState = STATE_NONE;		///<	�������Ȃ̂ňȑO�̃X�e�[�g�͂������������ׁASTATE_NONE�ɁB
	m_currentState = _FIRST_SETATE_;///<	�X�e�[�g�̏������Ȃ̂ōŏ��ɓǂݍ��ނł��낤�p�^�[���̒萔������
	ChangeState(m_currentState);	///<	�܂��X�e�[�g�|�C���g�ɂ͉��������Ă��Ȃ��̂ŏ����������˂�
	m_StageFrame.Init( 0.f, -2.f, WIDTH, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_));
	///<��ʏ㕔����P�P�}�X���ڂ܂ŔՖʃt���[��������̂�11/16�ƂȂ�B
	m_PlayerFrame[0].Init( _POS_PLAYER1FRAME_, _SIZE_PLAYERFRAME_ );
	m_PlayerFrame[1].Init( _POS_PLAYER2FRAME_, _SIZE_PLAYERFRAME_ );
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
void StateManager::StateDraw( CDrawManager* _drawManager)
{
	float tempX, tempY;
	
	//	�Ֆʘg�\���i���j
	m_StageFrame.GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		0.f, 0.f, 
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);

	//	�Ֆʘg�\���i�E�j
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*12, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 0.f, 
		1.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);

	//	�Ֆʘg�\���i���j
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*_STAGE_WIDTH_MAX_, tempY, 
		_BLOCK_WIDTH_SIZE_, HEIGHT,
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, 0.f,
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 1.f,
		180, 220, 220, 220);

	//	�v���C���[1�g�\��
	m_PlayerFrame[0].GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
		0.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		11/_BLOCK_WIDTH_MAX_, 1.f,
		180, 255, 100, 100);
	//	�v���C���[2�g�\��
	m_PlayerFrame[1].GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
		12/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		1.f, 1.f,
		180, 100, 100, 255);

	//	�X�e�[�W�}�X�ڕ\��
	for( int ip=0; ip<_PLAYER_NUM_; ip++ ){
		for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ ){
			for( int il=0; il<_STAGE_LINE_MAX_; il++ ){
				
				tempX = ( ic*( _BLOCK_WIDTH_SIZE_ ))+( _BLOCK_WIDTH_SIZE_ );
				tempY = ( il*( _BLOCK_HEIGHT_SIZE_ ))+( _BLOCK_HEIGHT_SIZE_ );
				if( ip == 1 )
					tempX += _BLOCK_WIDTH_SIZE_*11;

				_drawManager->CustomCorolDraw( _TEX_BLOCK_, tempX, tempY, 
					_BLOCK_WIDTH_SIZE_,  _BLOCK_HEIGHT_SIZE_,
					0.f, 0.f, 
					1.f, 1.f,
					100, 200, 200, 200);
			}
		}
	}
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

void StateManager::Free()
{
	delete m_pGameState;

}