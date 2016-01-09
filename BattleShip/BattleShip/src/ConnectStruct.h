#ifndef _CONNECTSTRUCT_H_
#define _CONNECTSTRUCT_H_

#include "StageDefineList.h"

struct ConnectShip {
	int m_userID;
	int m_posColumn;
	int m_posLine;
	int m_shipArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の実体配列
	int m_actionArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の攻撃範囲配列
	int m_searchArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の索敵範囲配列
	int m_moveArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の移動範囲配列
};

struct ConnectStage {
	int	m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<ステージ上の情報
};
#endif