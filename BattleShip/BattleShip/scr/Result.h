/**
*@file	Result.h
*@author	�T�c
*/

#ifndef _RESULT_H_
#define _RESULT_H_

#include "GameState.h"

class Result : public GameState
{
private:
	

public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	Result( ShipObject::_SHIP_TYPE_NUM_& _type ): GameState( _type ){}

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
	*@brief	�퓬���ʂł̒ʐM�ҋ@����
	*/
	bool ComStandby();

private:
	/**
	*@brief	�s���I���ɂ��퓬�̌���
	*@details	�퓬���ʂ́A�e��P�̍s���I���̌��ʂȂ̂ŁA����Ƃ��Ă͉��L�̂R��ނɂȂ�B
	*@param[in]	_playerIndex	�v���C���[�̔z��ł̎w��
	*@return �퓬����
	*@retval 0	���ɖ���
	*@retval 1	����̍U������������
	*@retval 2	����ɍ��G���ꂽ
	*/
	int ResultOfAction( int _playerIndex );
};

#endif