/**
*@file	BattleShip.h
*@author	亀田
*/

#include "BattleShip.h"

void BattleShip::Init()
{
	//	ファイル読み込みテスト
	ReadTableData( "table/BattleShip.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}