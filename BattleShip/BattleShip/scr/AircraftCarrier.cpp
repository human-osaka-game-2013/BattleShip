/**
*@file	AircraftCarrier.cpp
*@author	亀田
*/

#include "AircraftCarrier.h"

void AircraftCarrier::Init()
{
	//	ファイル読み込み
	ReadTableData( "table/AircraftCarrier.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}