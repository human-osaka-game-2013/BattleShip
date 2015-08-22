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
	bool m_SetCompFlag;	///<	Control�Ԃ�l���A��̔z�u�����t���O
	int m_SetCount;		///<	��̔z�u�񐔁i�ǂꂾ���z�u���Ă��邩�j
	
	
public:
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̏�����
	*/
	bool Init();

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

	/**
	*@brief	�Ֆʑ��`�F�b�N�̃��[�`������
	*@return	���茋��	0�F�N���b�N�̔����ʂ�Ȃ������B@n
				1�F�}�X�����łɖ��܂��Ă���or���̃}�X���ƒu���Ȃ��B@n
				2�F�N���b�N�����}�X�ɋ��z�u�o�����B
	*/
	int CheckBoard();

	/**
	*@brief	
	*/

	/**
	*@brief	�z�u�񐔂̎擾
	*/
	int GetSetCount(){ return m_SetCount; }
};

#endif