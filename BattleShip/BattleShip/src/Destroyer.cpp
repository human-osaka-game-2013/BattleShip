/**
*@file	Destroyer.h
*@author	亀田
*/

#include "Destroyer.h"

void Destroyer::Init()
{
	//	ファイル読み込みテスト
	ReadTableData( "table/Destroyer.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}