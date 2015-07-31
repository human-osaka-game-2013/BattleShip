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
	*@brief	������
	*/
	void Init( int _userID );

	/**
	*@brief	����擾
	*/
	ShipObject* GetShip( _SHIP_TYPE_NUM_ _shipType ) { return m_pShip[_shipType]; }
	
	/**
	*@brief	���[�U�[ID�擾
	*/
	int GetUserID(){ return m_userID; }
};

#endif 
