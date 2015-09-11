/**
*@file	Selection.h
*@author	�T�c
*/

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "GameState.h"

class Selection : public GameState
{


public:
	/**
	*@brief	�퓬�s���I���ł̏�����
	*/
	bool Init( ShipObject::_SHIP_TYPE_NUM_ _type );

	/**
	*@brief	�퓬�s���I���ł̃T�u���[�`������
	*/
	int Control();
	
	/**
	*@brief	�퓬�s���I���ł̕`��
	*/
	void Draw();
	
	/**
	*@brief	�퓬�s���I���ł̒ʐM�ҋ@����
	*/
	void ComStandby();

};

#endif