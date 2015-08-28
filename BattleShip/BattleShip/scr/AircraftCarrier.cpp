/**
*@file	AircraftCarrier.cpp
*@author	亀田
*/

#include "AircraftCarrier.h"

void AircraftCarrier::Init( int _userID )
{
	//	ファイル読み込みテスト
	ReadTableData( "table/AircraftCarrier.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}