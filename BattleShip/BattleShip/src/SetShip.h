/**
*@file	SetShip.h
*@author	�T�c
*/

#ifndef _SETSHIP_H_
#define _SETSHIP_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"

class SetShip : public GameState
{
private:
	
	
	
public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	SetShip( ShipObject::_SHIP_TYPE_NUM_& _type ): GameState( _type ){}

	~SetShip(){};

	/**
	*@brief	��z�u�ł̏�����
	*/
	bool Init();

	/**
	*@brief	��z�u�ł̃T�u���[�`������
	*@return	m_ShipCount	���݂̑I���������΁A���ʂ��󂯎����StateManager�́A@n
				����ɉ����ĈႤ�X�e�[�g�ɐ؂�ւ����肳����΂����B
	*/
	int Control();

	/**
	*@brief	��z�u�ł̃T�u���[�`���`��
	*/
	void Draw();
	
	/**
	*@brief	��z�u�ł̒ʐM�ҋ@����
	*/
	bool ComStandby();

	
	
private:	
	/**
	*@brief	�Ֆʑ��`�F�b�N�̃��[�`������
	*@return	���茋��	0�F�N���b�N�̔����ʂ�Ȃ������B@n
				1�F�}�X�����łɖ��܂��Ă���or���̃}�X���ƒu���Ȃ��B@n
				2�F�N���b�N�����}�X�ɋ��z�u�o�����B
	*/
	int CheckBoard();

	/**
	*@brief	�z�u�񐔂̎擾
	*/
	int GetSetCount(){ return m_ShipCount; }
};

#endif