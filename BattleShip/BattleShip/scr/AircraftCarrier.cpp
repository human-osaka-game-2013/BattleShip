/**
*@file	AircraftCarrier.cpp
*@author	�T�c
*/

#include "AircraftCarrier.h"

void AircraftCarrier::Init( int _userID )
{
	//	�t�@�C���ǂݍ��݃e�X�g
	ReadTableData( "table/AircraftCarrier.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}