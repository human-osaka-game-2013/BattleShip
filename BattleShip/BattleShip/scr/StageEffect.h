/**
*@file	StageEffect.h
*@author	�T�c
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

class StageEffect : public GameState
{


public:
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̏�����
	*/
	bool Init();

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