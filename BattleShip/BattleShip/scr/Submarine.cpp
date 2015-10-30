/**
*@file	Submarine.h
*@author	亀田
*/

#include "Submarine.h"

void Submarine::Init()
{
	//	ファイル読み込みテスト
	ReadTableData( "table/Submarine.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}