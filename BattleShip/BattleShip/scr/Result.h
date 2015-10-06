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
	*/
	int ResultOfAction();
};

#endif