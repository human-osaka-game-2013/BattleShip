/**
*@file	Submarine.h
*@author	‹T“c
*/

#include "Submarine.h"

void Submarine::Init( int _userID )
{
	ReadTableData( "../table/testTable.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}