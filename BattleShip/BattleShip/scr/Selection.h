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
	*@brief	�X�e�[�g�p�^�[�����ł̕`��
	*/
	bool Control();
	
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̕`��
	*/
	void Draw();
	
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̒ʐM���̃T�u���[�`������
	*/
	void ComStandby();

};

#endif