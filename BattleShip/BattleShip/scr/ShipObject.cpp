/**
*@file	ShipObject.cpp
*@author	�T�c
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

bool ShipObject::RotationShip( int _arrayType, bool _rotType )
{
	int tempArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];
	int tempArray2[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_] = {0};
	int (*_array)[_SHIP_ARRAY_INDEX_];	///<��]������z����i�[����|�C���^
	int (*_array2)[_SHIP_ARRAY_INDEX_] = NULL;
	CHARADIRECTION dir = GetDirection();

	switch( _arrayType )
	{
	case 0:	///<	��z��
		if( _rotType ){	///<�E��]
			if( dir+1 < CH_DIRECTION_MAX )
				SetDirection( (CHARADIRECTION)(dir+1) );
			else
				SetDirection( CH_LEFT );
		} else {		///<����]	
			if( dir-1 > CH_NONE )
				SetDirection( (CHARADIRECTION)(dir-1) );
			else
				SetDirection( CH_DOWN );
		}
		_array = m_shipArray;
		_array2 = m_moveArray;	///<	�����]��������ړ��z�����]������B
		
		break;	

	case 1:	///<	�U���͈͔z��
		_array = m_actionArray;
		break;

	case 2:	///<	���G�͈͔z��
		_array = m_searchArray;
		break;

	}

	// ��]�O�u���b�N���ꎞ�ۑ�
	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++)
	{
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++)
		{
			tempArray[iColumn][iLine] = _array[iColumn][iLine];
			if( _array2 != NULL )
				tempArray2[iColumn][iLine] = _array2[iColumn][iLine];
		}
	}

	// �u���b�N����]
	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++)
	{
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++)
		{
			if( _rotType ){
				_array[iColumn][iLine] = tempArray[iLine][(_SHIP_ARRAY_INDEX_-1)-iColumn];
				if( _array2 != NULL )
					_array2[iColumn][iLine] = tempArray2[iLine][(_SHIP_ARRAY_INDEX_-1)-iColumn];
			} else {
				_array[iColumn][iLine] = tempArray[(_SHIP_ARRAY_INDEX_-1)-iColumn][iLine];
				if( _array2 != NULL )
					_array2[iColumn][iLine] = tempArray2[(_SHIP_ARRAY_INDEX_-1)-iColumn][iLine];
			}
		}
	}
	return false;
}

void  ShipObject::Free()
{

}