/**
*@file	StageObject.h
*@author	�T�c
*/

#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "gameObject.h"
#include "ShipObject.h"
#include "BoardOfFrame.h"

#define _STAGE_COLUMN_MAX_ 10	///<	�X�e�[�W�̍s��
#define _STAGE_LINE_MAX_	10	///<	�X�e�[�W�̗�

#define _PLAYER_NUM_ 2

class StageObject : public CGameObject
{
public:
	unsigned char	m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<�X�e�[�W��̏��
	BoardOfFrame	m_stageBlock[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<�X�e�[�W�u���b�N�̍��W

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	StageObject() : CGameObject(){
			
	}

	bool Init();

	void Control(){};

	void Draw(){};

	/**
	*@brief	�X�e�[�W�u���b�N�̃`�F�b�N
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_vol	���肷��u���b�N�Ɣ�r����l
	*/
	bool CheckStageBlock( int _player, int _column, int _line, unsigned char _vol );
	
	void SetShip( ShipObject* _pShip );

	/**
	*@brief	�������
	*/
	void  Free();
};

#endif