#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ShipObject.h"
class Player
{
private:
	int m_userID;
	ShipObject	m_pShip[ShipObject::TYPE_MAX];

public:
	/**
	*@brief	‰Šú‰»
	*/
	void Init( int _userID );

	/**
	*@brief	‹îî•ñæ“¾
	*/
	ShipObject* GetShip( _SHIP_TYPE_NUM_ _shipType ) { return m_pShip[_shipType]; }
	
	/**
	*@brief	ƒ†[ƒU[IDæ“¾
	*/
	int GetUserID(){ return m_userID; }
};

#endif 
