/**
*@file	ShipObject.cpp
*@author	亀田
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
	int (*_array)[_SHIP_ARRAY_INDEX_];	///<回転させる配列を格納するポインタ
	int (*_array2)[_SHIP_ARRAY_INDEX_] = NULL;
	CHARADIRECTION dir = GetDirection();

	switch( _arrayType )
	{
	case 0:	///<	駒配列
		if( _rotType ){	///<右回転
			if( dir+1 < CH_DIRECTION_MAX )
				SetDirection( (CHARADIRECTION)(dir+1) );
			else
				SetDirection( (CHARADIRECTION)((int)CH_NONE+1) );
		} else {		///<左回転	
			if( dir-1 > CH_NONE )
				SetDirection( (CHARADIRECTION)(dir-1) );
			else
				SetDirection( (CHARADIRECTION)((int)CH_DIRECTION_MAX-1) );
		}
		_array = m_shipArray;
		_array2 = m_moveArray;	///<	駒を回転させたら移動配列も回転させる。
		
		break;	

	case 1:	///<	攻撃範囲配列
		_array = m_actionArray;
		break;

	case 2:	///<	索敵範囲配列
		_array = m_searchArray;
		break;

	}

	// 回転前ブロックを一時保存
	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++)
	{
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++)
		{
			tempArray[iColumn][iLine] = _array[iColumn][iLine];
			if( _array2 != NULL )
				tempArray2[iColumn][iLine] = _array2[iColumn][iLine];
		}
	}

	// ブロックを回転
	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++)
	{
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++)
		{
			if( _rotType ){
				_array[iColumn][iLine] = tempArray[(_SHIP_ARRAY_INDEX_-1)-iLine][iColumn];
				if( _array2 != NULL )
					_array2[iColumn][iLine] = tempArray2[iLine][(_SHIP_ARRAY_INDEX_-1)-iColumn];
			} else {
				_array[iLine][iColumn] = tempArray[(_SHIP_ARRAY_INDEX_-1)-iColumn][iLine];
				if( _array2 != NULL )
					_array2[iLine][iColumn] = tempArray2[(_SHIP_ARRAY_INDEX_-1)-iColumn][iLine];
			}
		}
	}


	return true;
}

void ShipObject::InitVertex( _SHIP_TYPE_NUM_ _shipType )
{
	int frontBlockNum;	///<	中心ブロックの前方にあるブロックの数
	int backBlockNum;	///<	中心ブロックの後方にあるブロックの数
	switch( _shipType )	///<	艦種別に設定
	{
		case TYPE_AIRCARRIER:
			frontBlockNum = 2;
			backBlockNum = 2;
			break;
		case TYPE_BATTLESHIP:
			frontBlockNum = 2;
			backBlockNum = 1;
			break;
		case TYPE_CRUISER:
			frontBlockNum = 1;
			backBlockNum = 1;
			break;
		case TYPE_DESTROYER:
		case TYPE_SUBMARINE:
			frontBlockNum = 1;
			backBlockNum = 0;
			break;
	}
	//	一ブロックのサイズは固定のため、↑で指定した数値基準で駒の中心ブロック基準の矩形を生成
	m_vertex[0].x = -_BLOCK_WIDTH_SIZE_/2;
	m_vertex[1].x = _BLOCK_WIDTH_SIZE_/2;
	m_vertex[2].x = _BLOCK_WIDTH_SIZE_/2;
	m_vertex[3].x = -_BLOCK_WIDTH_SIZE_/2;
	m_vertex[0].y = -_BLOCK_HEIGHT_SIZE_/2 -(_BLOCK_HEIGHT_SIZE_*frontBlockNum);
	m_vertex[1].y = -_BLOCK_HEIGHT_SIZE_/2 -(_BLOCK_HEIGHT_SIZE_*frontBlockNum);
	m_vertex[2].y = _BLOCK_HEIGHT_SIZE_/2 +(_BLOCK_HEIGHT_SIZE_*backBlockNum);
	m_vertex[3].y = _BLOCK_HEIGHT_SIZE_/2 +(_BLOCK_HEIGHT_SIZE_*backBlockNum);

	for (int i = 0; i < 4; i++) {
		m_vertex[i].z = 0.5f;
		m_vertex[i].rhw = 0.0f;
		m_vertex[i].color = 0xFFFFFFFF;
	}
	m_vertex[0].tu = 1.f;
	m_vertex[0].tv = 0.f;
	m_vertex[1].tu = 1.f;
	m_vertex[1].tv = 1.f;
	m_vertex[2].tu = 0.f;
	m_vertex[2].tv = 1.f;
	m_vertex[3].tu = 0.f;
	m_vertex[3].tv = 0.f;
}

void  ShipObject::Free()
{

}

void ShipObject::SetConnectShipData( ConnectShip* _pCShip )
{
	memmove_s(_pCShip->m_shipArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]),
							m_shipArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]));
	memmove_s(_pCShip->m_actionArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]),
							m_actionArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]));
	memmove_s(_pCShip->m_searchArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]),
							m_searchArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]));
	memmove_s(_pCShip->m_moveArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]),
							m_moveArray, sizeof(int [_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_]));
	_pCShip->m_userID = m_userID;
	_pCShip->m_posColumn = m_posColumn;
	_pCShip->m_posLine = m_posLine;
}

void ShipObject::SetShipData( ConnectShip* _pCShip )
{
	
}