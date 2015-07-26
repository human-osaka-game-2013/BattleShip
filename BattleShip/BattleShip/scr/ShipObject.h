/**
*@file	ShipObject.h
*@author	�T�c
*/

#ifndef _SHIPOBJECT_H_
#define _SHIPOBJECT_H_

#include "gameObject.h"

#define _SHIP_ARRAY_INDEX_	5	///<	��̔z��w��

/**
*@brief	��̊��N���X
*/
class ShipObject:public CGameObject
{
public:
	/**
	*@brief	��̎�ޗ�
	*/
	enum _SHIP_TYPE_NUM_
	{
		TYPE_NONE=-1,
		TYPE_AIRCARRIER,
		TYPE_BATTLESHIP,
		TYPE_CRUISER,
		TYPE_DESTROYER,
		TYPE_SUBMARINE,
		TYPE_MAX,
	};

private:
	int m_userID;

public:
	int m_shipArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̎��̔z��
	int m_actionArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̍s���͈͔z��B�U���Ȃǈړ��A���G�͈͂ȂǂɎg�p

public:
	/**
	*@brief
	*/
	ShipObject( _SHIP_TYPE_NUM_ _shipType, int _userID );

public:
	/**
	*@brief	��̎�����ID�擾
	*/
	int GetUserID(){ return m_userID; }	
};


#endif