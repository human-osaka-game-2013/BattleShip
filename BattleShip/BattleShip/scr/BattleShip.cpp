/**
*@file	BattleShip.h
*@author	�T�c
*/

#include "BattleShip.h"

void BattleShip::Init( int _userID )
{
	//	�t�@�C���ǂݍ��݃e�X�g
	ReadTableData( "table/testTable.csv", ShipObject::TABLE_MAX, _SHIP_ARRAY_INDEX_);
}