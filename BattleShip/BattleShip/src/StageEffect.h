/**
*@file	StageEffect.h
*@author	�T�c
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

#define _END_COUNT_OF_EFFECT_	60*10

class StageEffect : public GameState
{
private:
	int m_effectCount;	///<	�G�t�F�N�g���Đ�����ۂ̃J�E���^
	
public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	StageEffect( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		m_effectCount = 0;
	}

	~StageEffect(){};

	/**
	*@brief	�퓬�G�t�F�N�g�ł̏�����
	*/
	bool Init();

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
	bool ComStandby();

};

#endif