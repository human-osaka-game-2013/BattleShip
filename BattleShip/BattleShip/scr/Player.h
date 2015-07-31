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
	*@brief	������
	*/
	void Init( int _userID );

	/**
	*@brief	����擾
	*/
	ShipObject* GetShip( ShipObject::_SHIP_TYPE_NUM_ _shipType );
	
	/**
	*@brief	���[�U�[ID�擾
	*/
	int GetUserID(){ return m_userID; }
};

#endif 
