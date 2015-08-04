/**
*@file	Destroyer.h
*@author	‹T“c
*/

#include "Destroyer.h"

void Destroyer::Init( int _userID )
{
	ReadTableData( "../table/testTable.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
	//SetDirection();
}