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