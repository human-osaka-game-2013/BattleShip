/**
*@file	AircraftCarrier.cpp
*@author	�T�c
*/

#include "AircraftCarrier.h"

void AircraftCarrier::Init()
{
	//	�t�@�C���ǂݍ���
	ReadTableData( "table/AircraftCarrier.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}