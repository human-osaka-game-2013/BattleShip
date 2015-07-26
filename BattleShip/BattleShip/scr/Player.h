#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ShipObject.h"
class Player
{
private:
	int m_userID;
	ShipObject*	m_pShip;

public:
	Player( int _userID );

	ShipObject* GetShip( _SHIP_TYPE_NUM_ _shipType );

};

#endif 
