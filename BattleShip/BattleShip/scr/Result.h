/**
*@file	Result.h
*@author	�T�c
*/

#ifndef _RESULT_H_
#define _RESULT_H_

#include "GameState.h"

class Result : public GameState
{
	

public:
	/**
	*@brief	�퓬���ʂł̏�����
	*/
	bool Init( ShipObject::_SHIP_TYPE_NUM_ _type );

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
	void ComStandby();

};

#endif