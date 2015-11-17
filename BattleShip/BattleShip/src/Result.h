/**
*@file	Result.h
*@author	�T�c
*/

#ifndef _RESULT_H_
#define _RESULT_H_

#include "GameState.h"

#define _ANNIHILATION_NUM_ 16

class Result : public GameState
{
public:
	/**
	*@brief	�s���I���ɂ��̐퓬����
	*/	
	enum _ACTION_RESULT_
	{
		RESULT_NONE,
		RESULT_SEARCH,
		RESULT_ATTACK,
	};

	/**
	*@brief	�틵�̎��
	*/
	enum _PROGRESS_OF_BATTLE_TYPE_
	{
		TYPE_DEFEAT,		///<	�s�k
		TYPE_INFERIORITY,	///<	��
		TYPE_DRAW,			///<	��������
		TYPE_SUPERIORITY,	///<	�D��
		TYPE_VICTORY		///<	����
	};

private:
	int m_resultPlayer;	///<	�v���C���[���ɋN���Ă���퓬����
	int m_resultEnemy;	///<	�G���ɋN���Ă���퓬����
	int m_resultBattle;	///<	���҂̐틵����

public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	Result( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		m_resultPlayer	= 0;
		m_resultEnemy	= 0;
		m_resultBattle	= 0;
	}

	~Result(){};

	/**
	*@brief	�퓬���ʂł̏�����
	*/
	bool Init();

	/**
	*@brief	�퓬���ʂł̃T�u���[�`������

	*/
	int Control();
	
	/**
	*@brief	�퓬���ʂł̕`��
	*/
	void Draw();

	/**
	*@brief	�퓬���ʂ̎擾
	*@param[in] _resultPlayer
	*@param[in] _resultEnemy
	*/
	void GetResultPlayerAndEnemy( int& _resultPlayer, int& _resultEnemy )
	{
		_resultPlayer = m_resultPlayer;
		_resultEnemy = m_resultEnemy;
	}

	/**
	*@brief	�틵�̎擾
	*/
	void GetResultOfBattle( int& _resultBattle ){ _resultBattle = m_resultBattle; }

private:
	/**
	*@brief	�s���I���ɂ�錋��
	*@details	�퓬���ʂ́A�e��P�̍s���I���̌��ʂȂ̂ŁA����Ƃ��Ă͉��L�̂R��ނɂȂ�B
	*@param[in]	_playerIndex	�v���C���[�̔z��ł̎w��
	*@return �퓬����
	*@retval 0	���ɖ���
	*@retval 1	����̍U������������
	*@retval 2	����ɍ��G���ꂽ
	*/
	int ResultOfAction( const int _playerIndex );

	/**
	*@brief	�퓬�����̔���
	*@details	�퓬�����̔���������ۂ̃X�e�[�W���ɏ��̍X�V�����Ă��
	*@param[out] _iReturn
	*@param[in]	_plIndex
	*@param[in]	_column
	*@param[in]	_line
	*@param[in]	_selectNum
	*@param[in]	_shipNum
	*/
	void JudgmentOfActionProcess( int& _iReturn, const int _plIndex, int& _column, int& _line,
									const int _selectNum, const int _shipNum );

	/**
	*@brief	�퓬���ʂɂ��틵����
	*@details	�v���C���[�e�X�̋�̑��Q������A_PROGRESS_OF_BATTLE_TYPE_�ɉ������l��Ԃ�
	*@param[in]	_playerIndex �v���C���[���̎w��
	*@param[in]	_enemyIndex �G���̎w��
	*@return	_PROGRESS_OF_BATTLE_TYPE_�ɍ��킹���l
	*/
	int ResultProgressOfBattle( const int _playerIndex, const int _enemyIndex );
};

#endif