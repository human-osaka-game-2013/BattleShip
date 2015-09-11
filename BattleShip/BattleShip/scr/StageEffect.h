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
	*@brief	�퓬�G�t�F�N�g�ł̏�����
	*/
	bool Init( ShipObject::_SHIP_TYPE_NUM_ _type );

	/**
	*@brief	�퓬�G�t�F�N�g�ł̃T�u���[�`������
	*/
	int Control();
	
	/**
	*@brief	�퓬�G�t�F�N�g�ł̕`��
	*/
	void Draw();
	
	/**
	*@brief	�퓬�G�t�F�N�g�ł̒ʐM�ҋ@����
	*/
	void ComStandby();

};

#endif