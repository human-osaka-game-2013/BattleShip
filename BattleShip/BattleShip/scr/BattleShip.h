/**
*@file	BattleShip.h
*@author	�T�c
*/

#ifndef _BATTLESHIP_H_
#define _BATTLESHIP_H_

#include "ShipObject.h"

class BattleShip : public ShipObject
{

public:
	/**
	*@brief �R���X�g���N�^
	*/
	BattleShip::BattleShip( int _userID ):ShipObject( _userID )
	{

	}

	void Init();

};


#endif