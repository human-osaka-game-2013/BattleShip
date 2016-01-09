#ifndef _CONNECTSTRUCT_H_
#define _CONNECTSTRUCT_H_

#include "StageDefineList.h"

struct ConnectShip {
	int m_userID;
	int m_posColumn;
	int m_posLine;
	int m_shipArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̎��̔z��
	int m_actionArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̍U���͈͔z��
	int m_searchArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̍��G�͈͔z��
	int m_moveArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̈ړ��͈͔z��
};

struct ConnectStage {
	int	m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<�X�e�[�W��̏��
};
#endif