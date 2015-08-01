/**
*@file	Destroyer.h
*@author	‹T“c
*/

#include "Destroyer.h"

void Destroyer::Init( int _userID )
{
	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn ){
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine )	{
			m_shipArray[iColumn][iLine]=0;
			m_actionArray[iColumn][iLine]=0;
		}
	}
}