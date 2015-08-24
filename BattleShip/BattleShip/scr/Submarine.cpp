/**
*@file	Submarine.h
*@author	亀田
*/

#include "Submarine.h"

void Submarine::Init( int _userID )
{
	//	ファイル読み込みテスト
	ReadTableData( "table/testTable.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}