/**
*@file	SetShip.h
*@author	�T�c
*/

#ifndef _SETSHIP_H_
#define _SETSHIP_H_

#include "GameState.h"

class SetShip : public GameState
{
private:


public:
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̃T�u���[�`������
	*/
	bool Control();

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̃T�u���[�`������
	*/
	void Draw();
	
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̃T�u���[�`������
	*/
	void ComStandby();

};

#endif