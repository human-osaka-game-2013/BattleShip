/**
*@file	Destroyer.h
*@author	�T�c
*/

#include "Destroyer.h"

void Destroyer::Init()
{
	//	�t�@�C���ǂݍ��݃e�X�g
	ReadTableData( "table/Destroyer.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}