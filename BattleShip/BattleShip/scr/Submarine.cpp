/**
*@file	Submarine.h
*@author	�T�c
*/

#include "Submarine.h"

void Submarine::Init()
{
	//	�t�@�C���ǂݍ��݃e�X�g
	ReadTableData( "table/Submarine.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}