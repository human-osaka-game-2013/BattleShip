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
	int				m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<�X�e�[�W��̏��
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
	
	/**
	*@brief	�X�e�[�W�u���b�N�̃`�F�b�N(��Ƃ̔���)
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_ship	�w�肵���u���b�N���S�ɔ�r�����̃|�C���^
	*@return	0�F�X�e�[�W��̎w��͈͂ƃu���b�N�̎��̂��ڐG���Ă��Ȃ��ꍇ�B@n
				1�F�X�e�[�W�O�Ƀu���b�N�̎��̂��������ꍇ�B@n
				2�F�w�肵���u���b�N�͈̔͂ɂ��łɃX�e�[�W��ŉ��������݂��Ă����ꍇ�B@n
				-1�F��L�ȊO�̎������������ꍇ�B
	*/
	int CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship );
	
	/**
	*@brief	�X�e�[�W�u���b�N�֋�����Z�b�g
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_ship	�w�肵���u���b�N���S�ɃZ�b�g�����̃|�C���^
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool SetShip( int _player, int _column, int _line, ShipObject* _ship );

	/**
	*@brief	�X�e�[�W�u���b�N�֎w��͈͏����Z�b�g
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_array	�w�肵���u���b�N���S�ɃZ�b�g����z����
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool SetRange( int _player, int _column, int _line, const int(*_array)[_SHIP_ARRAY_INDEX_], int _setType);

	/**
	*@brief	�X�e�[�W�u���b�N�̑I����Ԃ�����
	*/
	void ResetSelect();

	/**
	*@brief	�������
	*/
	void  Free();
};

#endif