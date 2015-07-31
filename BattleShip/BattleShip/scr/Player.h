#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <list>
#include "ShipObject.h"


class Player
{
private:
	int m_userID;
	std::list<*ShipObject> m_pShip;

public:
	/**
	*@brief	‰Šú‰»
	*/
	void Init( int _userID );

	/**
	*@brief	‹îî•ñæ“¾
	*/
	ShipObject* GetShip( ShipObject::_SHIP_TYPE_NUM_ _shipType );
	
	/**
	*@brief	ƒ†[ƒU[IDæ“¾
	*/
	int GetUserID(){ return m_userID; }
};

#endif 
