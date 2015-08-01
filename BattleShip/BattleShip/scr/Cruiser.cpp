/**
*@file	Cruiser.h
*@author	‹T“c
*/

#include "Cruiser.h"

void Cruiser::Init( int _userID )
{
	ReadTableData( "../table/testTable.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}