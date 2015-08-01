/**
*@file	ShipObject.cpp
*@author	‹T“c
*/

#include "ShipObject.h"

void ShipObject::SetTable( char* _p, int _iColumn, int _iLine)
{
	int iColumnTemp = _iColumn%_SHIP_ARRAY_INDEX_;
	int iTemp = atoi(_p);

	if( _iColumn < TABLE_ACTION )
	{
		m_shipArray[iColumnTemp][_iLine] = iTemp;
	}
	else if( _iColumn < TABLE_SEARCH )
	{
		m_actionArray[iColumnTemp][_iLine] = iTemp;
	}
	else if( _iColumn < TABLE_MOVE )
	{
		m_searchArray[iColumnTemp][_iLine] = iTemp;
	}
	else
	{
		m_moveArray[iColumnTemp][_iLine] = iTemp;
	}
}