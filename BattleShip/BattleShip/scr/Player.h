#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "ShipObject.h"
#include "AircraftCarrier.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"

class Player
{
private:
	int m_userID;
	std::vector<ShipObject*> m_pShip;

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	Player( int _userID ): m_userID( _userID )
	{
		Init( m_userID );
	}

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
